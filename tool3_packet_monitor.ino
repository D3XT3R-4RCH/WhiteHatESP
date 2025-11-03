/*
 * Tool 3: Network Packet Monitor (ENHANCED)
 * Monitors WiFi traffic in real-time with advanced details
 * Created by: D3XT3R-4RCH
 */

// General statistics variables
unsigned long totalPackets = 0;
unsigned long mgmtPackets = 0;
unsigned long ctrlPackets = 0;
unsigned long dataPackets = 0;
unsigned long monitorStartTime = 0;

// Variables for detailed Management analysis
unsigned long beacons = 0;
unsigned long probeRequests = 0;
unsigned long probeResponses = 0;
unsigned long authFrames = 0;
unsigned long deauthFrames = 0;
unsigned long assocFrames = 0;
unsigned long disassocFrames = 0;

// Structure to track unique devices
#define MAX_DEVICES 30
struct DeviceInfo {
  uint8_t mac[6];
  unsigned long packets;
  bool active;
};

DeviceInfo devices[MAX_DEVICES];
int numDevices = 0;

// Enhanced callback to analyze packets in detail
void IRAM_ATTR analyzePacketsDetailed(void* buf, wifi_promiscuous_pkt_type_t type) {
  const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
  const uint8_t *frame = pkt->payload;
  const uint16_t frameLen = pkt->rx_ctrl.sig_len;
  
  totalPackets++;
  
  if (type == WIFI_PKT_MGMT) {
    mgmtPackets++;
    
    // Analyze Management frame subtype
    const uint8_t frameType = frame[0];
    const uint8_t frameSubType = (frameType & 0xF0) >> 4;
    
    switch(frameSubType) {
      case 0x00: // Association Request
      case 0x01: // Association Response
        assocFrames++;
        break;
      case 0x04: // Probe Request
        probeRequests++;
        break;
      case 0x05: // Probe Response
        probeResponses++;
        break;
      case 0x08: // Beacon
        beacons++;
        break;
      case 0x0B: // Authentication
        authFrames++;
        break;
      case 0x0C: // Deauthentication
        deauthFrames++;
        break;
      case 0x0A: // Disassociation
        disassocFrames++;
        break;
    }
    
    // Extract source MAC address (bytes 10-15)
    if (frameLen > 15 && numDevices < MAX_DEVICES) {
      const uint8_t *srcMac = &frame[10];
      
      // Check if this device already exists
      bool found = false;
      for (int i = 0; i < numDevices; i++) {
        if (memcmp(devices[i].mac, srcMac, 6) == 0) {
          devices[i].packets++;
          devices[i].active = true;
          found = true;
          break;
        }
      }
      
      // If new, add it
      if (!found && numDevices < MAX_DEVICES) {
        memcpy(devices[numDevices].mac, srcMac, 6);
        devices[numDevices].packets = 1;
        devices[numDevices].active = true;
        numDevices++;
      }
    }
    
  } else if (type == WIFI_PKT_CTRL) {
    ctrlPackets++;
  } else if (type == WIFI_PKT_DATA) {
    dataPackets++;
  }
}

void packetMonitor() {
  Serial.println(">> Network Packet Monitor (ENHANCED) <<");
  Serial.println("Analyzing WiFi traffic with advanced details...");
  Serial.println("Press 's' to stop\n");
  
  // Reset counters
  totalPackets = 0;
  mgmtPackets = 0;
  ctrlPackets = 0;
  dataPackets = 0;
  beacons = 0;
  probeRequests = 0;
  probeResponses = 0;
  authFrames = 0;
  deauthFrames = 0;
  assocFrames = 0;
  disassocFrames = 0;
  numDevices = 0;
  
  // Clear devices array
  memset(devices, 0, sizeof(devices));
  
  monitorStartTime = millis();
  
  // Configure promiscuous mode
  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();
  delay(100);
  
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&analyzePacketsDetailed);
  
  int channel = 1;
  bool continueMonitoring = true;
  int cycle = 0;
  
  while (continueMonitoring) {
    // Change channel
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    
    delay(1000);
    
    // Show statistics every 5 seconds
    cycle++;
    if (cycle % 5 == 0) {
      unsigned long elapsedTime = (millis() - monitorStartTime) / 1000;
      
      Serial.println("\n╔═══════════════════════════════════════════════════════════╗");
      Serial.println("║        DETAILED WiFi TRAFFIC STATISTICS                  ║");
      Serial.println("╠═══════════════════════════════════════════════════════════╣");
      Serial.printf("║ Current channel: %-40d║\n", channel);
      Serial.printf("║ Time: %-51lu s ║\n", elapsedTime);
      Serial.println("╠═══════════════════════════════════════════════════════════╣");
      Serial.printf("║ Total packets: %-42lu║\n", totalPackets);
      Serial.printf("║ - Management: %-43lu║\n", mgmtPackets);
      Serial.printf("║ - Control: %-46lu║\n", ctrlPackets);
      Serial.printf("║ - Data: %-49lu║\n", dataPackets);
      Serial.println("╠═══════════════════════════════════════════════════════════╣");
      
      // Detailed Management breakdown
      Serial.println("║ MANAGEMENT PACKETS BREAKDOWN:                            ║");
      Serial.printf("║   • Beacons (routers announcing): %-22lu║\n", beacons);
      Serial.printf("║   • Probe Requests (WiFi search): %-22lu║\n", probeRequests);
      Serial.printf("║   • Probe Responses: %-36lu║\n", probeResponses);
      Serial.printf("║   • Authentication: %-37lu║\n", authFrames);
      Serial.printf("║   • Association: %-39lu║\n", assocFrames);
      Serial.printf("║   • Deauth/Disassoc: %-36lu║\n", deauthFrames + disassocFrames);
      Serial.println("╠═══════════════════════════════════════════════════════════╣");
      
      if (elapsedTime > 0) {
        float packetsPerSec = (float)totalPackets / elapsedTime;
        Serial.printf("║ Rate: %.2f packets/second%-31s║\n", packetsPerSec, "");
      }
      
      Serial.printf("║ Unique devices detected: %-32d║\n", numDevices);
      Serial.println("╚═══════════════════════════════════════════════════════════╝\n");
      
      // Show top 5 most active devices
      if (numDevices > 0) {
        Serial.println("┌───────────────────────────────────────────────────────────┐");
        Serial.println("│       TOP MOST ACTIVE DEVICES (by packets)               │");
        Serial.println("├───────────────────────────────────────────────────────────┤");
        
        // Sort by packet count (simple bubble sort)
        for (int i = 0; i < numDevices - 1; i++) {
          for (int j = 0; j < numDevices - i - 1; j++) {
            if (devices[j].packets < devices[j + 1].packets) {
              DeviceInfo temp = devices[j];
              devices[j] = devices[j + 1];
              devices[j + 1] = temp;
            }
          }
        }
        
        // Show top 5
        int toShow = numDevices > 5 ? 5 : numDevices;
        for (int i = 0; i < toShow; i++) {
          Serial.printf("│ %d. MAC: %02X:%02X:%02X:%02X:%02X:%02X  |  Packets: %-12lu│\n",
                        i + 1,
                        devices[i].mac[0], devices[i].mac[1],
                        devices[i].mac[2], devices[i].mac[3],
                        devices[i].mac[4], devices[i].mac[5],
                        devices[i].packets);
        }
        Serial.println("└───────────────────────────────────────────────────────────┘\n");
      }
      
      // Activity analysis
      Serial.println("📊 ACTIVITY ANALYSIS:");
      
      if (beacons > mgmtPackets * 0.6) {
        Serial.println("  ✓ NORMAL activity: Majority are router beacons");
      }
      
      if (probeRequests > mgmtPackets * 0.3) {
        Serial.println("  ℹ️ HIGH WiFi network search activity");
        Serial.println("     (Devices searching for known networks)");
      }
      
      if (deauthFrames > 10) {
        Serial.println("  ⚠️ ALERT: Deauthentication packets detected!");
        Serial.printf("     Total deauth/disassoc: %lu\n", deauthFrames + disassocFrames);
        digitalWrite(LED_PIN, HIGH);
        delay(300);
        digitalWrite(LED_PIN, LOW);
      }
      
      if (authFrames > 0 || assocFrames > 0) {
        Serial.printf("  🔗 Devices connecting: Auth=%lu, Assoc=%lu\n", 
                      authFrames, assocFrames);
      }
      
      Serial.println();
    }
    
    // Rotate channels
    channel++;
    if (channel > 13) channel = 1;
    
    // Check if user wants to exit
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == 's' || c == 'S') {
        continueMonitoring = false;
      }
    }
  }
  
  // Disable promiscuous mode
  esp_wifi_set_promiscuous(false);
  
  Serial.println("\n╔═══════════════════════════════════════════════════════════╗");
  Serial.println("║                    FINAL SUMMARY                         ║");
  Serial.println("╠═══════════════════════════════════════════════════════════╣");
  Serial.printf("║ Total packets captured: %-33lu║\n", totalPackets);
  Serial.printf("║ Total time: %-45lu s ║\n", (millis() - monitorStartTime) / 1000);
  Serial.printf("║ Unique devices: %-41d║\n", numDevices);
  Serial.println("╠═══════════════════════════════════════════════════════════╣");
  Serial.println("║ FINAL BREAKDOWN:                                         ║");
  Serial.printf("║ Beacons: %-48lu║\n", beacons);
  Serial.printf("║ Probe Requests: %-41lu║\n", probeRequests);
  Serial.printf("║ Probe Responses: %-40lu║\n", probeResponses);
  Serial.printf("║ Auth/Assoc: %-45lu║\n", authFrames + assocFrames);
  Serial.printf("║ Deauth/Disassoc: %-40lu║\n", deauthFrames + disassocFrames);
  Serial.printf("║ Control: %-48lu║\n", ctrlPackets);
  Serial.printf("║ Data: %-51lu║\n", dataPackets);
  Serial.println("╚═══════════════════════════════════════════════════════════╝\n");
  
  Serial.println("💡 INTERPRETATION:");
  Serial.println("  • Beacons: Routers announcing their presence");
  Serial.println("  • Probe Requests: Devices searching for WiFi networks");
  Serial.println("  • Auth/Assoc: Devices connecting to networks");
  Serial.println("  • Deauth: Disconnections (normal or attacks)");
  Serial.println();
}
