/*
 * Tool 2: Deauth Detection & Alert
 * Detects deauthentication attacks on WiFi networks
 * Created by: D3XT3R-4RCH
 */

// Detection variables
unsigned long startTime = 0;
int deauthPackets = 0;
const int DEAUTH_THRESHOLD = 10; // Suspicious packet threshold

// Callback to analyze WiFi packets
void IRAM_ATTR analyzePacket(void* buf, wifi_promiscuous_pkt_type_t type) {
  if (type != WIFI_PKT_MGMT) return;
  
  const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
  const uint8_t *frame = pkt->payload;
  const uint8_t frameType = frame[0];
  
  // 0xC0 = Deauthentication packet
  // 0xA0 = Disassociation packet
  if (frameType == 0xC0 || frameType == 0xA0) {
    deauthPackets++;
  }
}

void deauthDetection() {
  Serial.println(">> Deauth Detection & Alert <<");
  Serial.println("Monitoring for deauthentication attacks...");
  Serial.println("Press 's' to stop\n");
  
  deauthPackets = 0;
  startTime = millis();
  
  // Configure promiscuous mode
  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();
  delay(100);
  
  // Configure callback for packet capture
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&analyzePacket);
  
  // Scan all channels
  int channel = 1;
  bool continueMonitoring = true;
  
  while (continueMonitoring) {
    // Change channel every 2 seconds
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    Serial.printf("Channel %d | Deauth detected: %d\n", channel, deauthPackets);
    
    // Check if attack is in progress
    unsigned long elapsedTime = (millis() - startTime) / 1000;
    
    if (deauthPackets > DEAUTH_THRESHOLD) {
      Serial.println("\n⚠️⚠️⚠️ ALERT: POSSIBLE ATTACK DETECTED ⚠️⚠️⚠️");
      Serial.printf("Detected %d deauth packets in %lu seconds\n", 
                    deauthPackets, elapsedTime);
      
      // Visual alert with LED
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
      }
    }
    
    delay(2000);
    
    // Rotate channels (1-13)
    channel++;
    if (channel > 13) {
      channel = 1;
      
      // Show statistics every complete cycle
      Serial.println("\n--- Statistics ---");
      Serial.printf("Monitoring time: %lu seconds\n", elapsedTime);
      Serial.printf("Total deauth packets: %d\n", deauthPackets);
      
      if (deauthPackets == 0) {
        Serial.println("✓ No attacks detected");
      }
      
      Serial.println("-------------------\n");
    }
    
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
  
  Serial.println("\nMonitoring stopped.");
  Serial.printf("Total deauth packets detected: %d\n", deauthPackets);
}
