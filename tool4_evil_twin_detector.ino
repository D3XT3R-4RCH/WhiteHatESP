/*
 * Tool 4: Evil Twin Detector
 * Detects fake or duplicated access points
 * Created by: D3XT3R-4RCH
 */

struct NetworkInfo {
  String ssid;
  String bssid;
  int rssi;
  int channel;
};

#include "configuracion.h"

void evilTwinDetector() {
  Serial.println(">> Evil Twin Detector <<");
  Serial.println("Detecting duplicated access points...\n");
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  // First scan
  Serial.println("Performing initial scan...");
  int numNetworks = WiFi.scanNetworks();
  
  if (numNetworks == 0) {
    Serial.println("No WiFi networks found");
    return;
  }
  
  // Store network information
  NetworkInfo networks[numNetworks];
  for (int i = 0; i < numNetworks; i++) {
    networks[i].ssid = WiFi.SSID(i);
    networks[i].bssid = WiFi.BSSIDstr(i);
    networks[i].rssi = WiFi.RSSI(i);
    networks[i].channel = WiFi.channel(i);
  }
  
  Serial.printf("Found %d networks. Analyzing...\n\n", numNetworks);
  
  // Search for duplicate SSIDs
  bool evilTwinFound = false;
  
  for (int i = 0; i < numNetworks; i++) {
    for (int j = i + 1; j < numNetworks; j++) {
      // Same SSID but different BSSID = Possible Evil Twin
      if (networks[i].ssid == networks[j].ssid && 
          networks[i].bssid != networks[j].bssid &&
          networks[i].ssid != "") {
        
        evilTwinFound = true;
        
        Serial.println("⚠️⚠️⚠️ POSSIBLE EVIL TWIN DETECTED ⚠️⚠️⚠️\n");
        Serial.printf("Duplicate SSID: %s\n\n", networks[i].ssid.c_str());
        
        // Compare against a saved known router MAC (if provided)
        String knownMac = String(KNOWN_ROUTER_MAC);
        bool hasKnownMac = (knownMac.length() > 0);
        bool ap1IsKnown = false;
        bool ap2IsKnown = false;
        if (hasKnownMac) {
          ap1IsKnown = networks[i].bssid.equalsIgnoreCase(knownMac);
          ap2IsKnown = networks[j].bssid.equalsIgnoreCase(knownMac);
        }

        Serial.println("AP #1:");
        Serial.print("  MAC (BSSID): ");
        Serial.print(networks[i].bssid);
        if (ap1IsKnown) Serial.print("  <- KNOWN ROUTER");
        Serial.println();
        Serial.printf("  Channel: %d\n", networks[i].channel);
        Serial.printf("  Signal: %d dBm\n", networks[i].rssi);
        
  Serial.println("\nAP #2:");
  Serial.print("  MAC (BSSID): ");
  Serial.print(networks[j].bssid);
  if (ap2IsKnown) Serial.print("  <- KNOWN ROUTER");
  Serial.println();
  Serial.printf("  Channel: %d\n", networks[j].channel);
  Serial.printf("  Signal: %d dBm\n", networks[j].rssi);
        
        Serial.println("\n📋 ANALYSIS:");
        
        // Signal analysis
        if (abs(networks[i].rssi - networks[j].rssi) < 10) {
          Serial.println("  • Similar signals - SUSPICIOUS");
        } else {
          Serial.println("  • Different signals - Could be legitimate");
        }
        
        // Channel analysis
        if (networks[i].channel == networks[j].channel) {
          Serial.println("  • Same channel - VERY SUSPICIOUS");
        } else {
          Serial.println("  • Different channels - Less suspicious");
        }
        
        Serial.println("\n⚠️ RECOMMENDATION:");
        if (hasKnownMac) {
          if (ap1IsKnown && !ap2IsKnown) {
            Serial.println("  AP #1 matches your saved router MAC.");
            Serial.println("  AP #2 does NOT match — treat AP #2 as suspicious.");
            Serial.println("  DO NOT connect to AP #2.");
          } else if (ap2IsKnown && !ap1IsKnown) {
            Serial.println("  AP #2 matches your saved router MAC.");
            Serial.println("  AP #1 does NOT match — treat AP #1 as suspicious.");
            Serial.println("  DO NOT connect to AP #1.");
          } else if (ap1IsKnown && ap2IsKnown) {
            Serial.println("  Both APs match your saved MAC — this is unusual.");
            Serial.println("  Double-check your router and consider rebooting it.");
          } else {
            Serial.println("  Neither AP matches the saved MAC.");
            Serial.println("  Compare the MACs above with your router's MAC in \"configuracion.h\".");
            Serial.println("  DO NOT connect to suspicious APs until verified.");
          }
        } else {
          Serial.println("  Verify which is your legitimate AP by comparing");
          Serial.println("  the MAC address with your router's (not configured).");
          Serial.println("  To help future detections, set KNOWN_ROUTER_MAC in configuracion.h");
          Serial.println("  DO NOT connect to the suspicious AP.\n");
        }
        
        Serial.println("========================================\n");
        
        // Visual alert
        for (int k = 0; k < 3; k++) {
          digitalWrite(LED_PIN, HIGH);
          delay(300);
          digitalWrite(LED_PIN, LOW);
          delay(300);
        }
      }
    }
  }
  
  if (!evilTwinFound) {
    Serial.println("✓ No duplicate SSIDs detected");
    Serial.println("✓ No obvious Evil Twins found\n");
  }
  
  // Show all networks found
  Serial.println("=== COMPLETE NETWORK LIST ===\n");
  for (int i = 0; i < numNetworks; i++) {
    Serial.printf("%d. %s\n", i+1, networks[i].ssid.c_str());
    Serial.printf("   MAC: %s | Channel: %d | Signal: %d dBm\n", 
                  networks[i].bssid.c_str(), networks[i].channel, networks[i].rssi);
    Serial.println();
  }
  
  Serial.println("💡 TIP: Save your legitimate router's MAC");
  Serial.println("   for future comparisons.\n");
  
  WiFi.scanDelete();
}
