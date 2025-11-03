/*
 * Tool 1: WiFi Security Scanner
 * Scans WiFi networks and detects insecure configurations
 * Created by: D3XT3R-4RCH
 */

void wifiSecurityScanner() {
  Serial.println(">> WiFi Security Scanner <<");
  Serial.println("Starting WiFi network scan...\n");
  
  // Configure WiFi in station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  // Scan available networks
  int numNetworks = WiFi.scanNetworks();
  
  if (numNetworks == 0) {
    Serial.println("No WiFi networks found");
  } else {
    Serial.printf("Found %d networks:\n\n", numNetworks);
    
    // Display information for each network
    for (int i = 0; i < numNetworks; i++) {
      Serial.printf("Network #%d:\n", i + 1);
      Serial.printf("  SSID: %s\n", WiFi.SSID(i).c_str());
      Serial.printf("  RSSI: %d dBm ", WiFi.RSSI(i));
      
      // Signal strength indicator
      if (WiFi.RSSI(i) > -50) {
        Serial.println("(Excellent)");
      } else if (WiFi.RSSI(i) > -60) {
        Serial.println("(Good)");
      } else if (WiFi.RSSI(i) > -70) {
        Serial.println("(Fair)");
      } else {
        Serial.println("(Weak)");
      }
      
      // Encryption type
      Serial.printf("  Channel: %d\n", WiFi.channel(i));
      Serial.print("  Security: ");
      
      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN:
          Serial.println("OPEN ⚠️ INSECURE!");
          digitalWrite(LED_PIN, HIGH);
          delay(100);
          digitalWrite(LED_PIN, LOW);
          break;
        case WIFI_AUTH_WEP:
          Serial.println("WEP ⚠️ OBSOLETE AND VERY INSECURE!");
          break;
        case WIFI_AUTH_WPA_PSK:
          Serial.println("WPA ⚠️ VULNERABLE");
          break;
        case WIFI_AUTH_WPA2_PSK:
          Serial.println("WPA2 ✓ Secure");
          break;
        case WIFI_AUTH_WPA_WPA2_PSK:
          Serial.println("WPA/WPA2 ✓ Acceptable");
          break;
        case WIFI_AUTH_WPA2_ENTERPRISE:
          Serial.println("WPA2 Enterprise ✓✓ Very Secure");
          break;
        case WIFI_AUTH_WPA3_PSK:
          Serial.println("WPA3 ✓✓✓ Excellent!");
          break;
        default:
          Serial.println("Unknown");
      }
      
      Serial.printf("  MAC: %s\n", WiFi.BSSIDstr(i).c_str());
      Serial.println("  ---");
    }
    
    // Security summary
    Serial.println("\n=== SECURITY SUMMARY ===");
    int openNetworks = 0;
    int wepNetworks = 0;
    
    for (int i = 0; i < numNetworks; i++) {
      if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
        openNetworks++;
      } else if (WiFi.encryptionType(i) == WIFI_AUTH_WEP) {
        wepNetworks++;
      }
    }
    
    Serial.printf("Open networks (no security): %d\n", openNetworks);
    Serial.printf("WEP networks (insecure): %d\n", wepNetworks);
    
    if (openNetworks > 0 || wepNetworks > 0) {
      Serial.println("⚠️ Insecure network configurations detected");
    } else {
      Serial.println("✓ All networks have acceptable security");
    }
  }
  
  // Clean scan results
  WiFi.scanDelete();
}
