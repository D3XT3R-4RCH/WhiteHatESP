/*
 * Tool 5: Port Scanner
 * Scans open ports on local network devices
 * Created by: D3XT3R-4RCH
 */

// Common ports to scan
const int commonPorts[] = {
  21,    // FTP
  22,    // SSH
  23,    // Telnet
  25,    // SMTP
  53,    // DNS
  80,    // HTTP
  443,   // HTTPS
  445,   // SMB
  3306,  // MySQL
  3389,  // RDP
  5000,  // UPnP
  8080,  // HTTP Alt
  8888   // HTTP Alt
};

const int numPorts = sizeof(commonPorts) / sizeof(commonPorts[0]);

void portScanner() {
  Serial.println(">> Port Scanner <<");
  Serial.println("Port scanner for local network\n");
  
  // First we need to connect to a WiFi network
  Serial.println("To scan ports, you must be connected to a WiFi network.");
  Serial.println("Enter your network SSID:");
  
  // Clear serial buffer first
  while(Serial.available()) Serial.read();
  
  // Wait for user input
  while (Serial.available() == 0) {
    delay(100);
  }
  
  String ssid = Serial.readStringUntil('\n');
  ssid.trim();
  
  // Clear buffer again
  while(Serial.available()) Serial.read();
  
  Serial.println("Enter the password:");
  
  // Wait for password input
  while (Serial.available() == 0) {
    delay(100);
  }
  
  String password = Serial.readStringUntil('\n');
  password.trim();
  
  // Clear buffer
  while(Serial.available()) Serial.read();
  
  // Properly disconnect and reset WiFi
  WiFi.disconnect(true);
  delay(500);
  WiFi.mode(WIFI_OFF);
  delay(500);
  
  // Connect to WiFi
  Serial.printf("\nConnecting to %s...\n", ssid.c_str());
  WiFi.mode(WIFI_STA);
  delay(100);
  WiFi.begin(ssid.c_str(), password.c_str());
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println();
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ Could not connect to WiFi network");
    Serial.println("Check SSID and password");
    return;
  }
  
  Serial.println("✓ Successfully connected!");
  Serial.printf("Assigned IP: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("Gateway: %s\n\n", WiFi.gatewayIP().toString().c_str());
  
  // Ask for target IP
  Serial.println("Enter IP to scan (e.g: 192.168.1.1):");
  Serial.println("Or press ENTER to scan the gateway:");
  
  // Clear buffer
  while(Serial.available()) Serial.read();
  
  // Wait for IP input
  while (Serial.available() == 0) {
    delay(100);
  }
  
  String ipStr = Serial.readStringUntil('\n');
  ipStr.trim();
  
  // Clear buffer
  while(Serial.available()) Serial.read();
  
  // If no IP entered, use gateway
  if (ipStr.length() == 0) {
    ipStr = WiFi.gatewayIP().toString();
  }
  
  Serial.printf("\n╔═══════════════════════════════════════╗\n");
  Serial.printf("║   Scanning: %-26s║\n", ipStr.c_str());
  Serial.printf("╚═══════════════════════════════════════╝\n\n");
  
  WiFiClient client;
  int openPorts = 0;
  
  Serial.println("Port     Status     Service");
  Serial.println("------   -------    --------");
  
  for (int i = 0; i < numPorts; i++) {
    int port = commonPorts[i];
    
    // Try to connect to port
    if (client.connect(ipStr.c_str(), port, 1000)) {
      openPorts++;
      Serial.printf("%-8d OPEN       ", port);
      
      // Identify service
      switch(port) {
        case 21:   Serial.println("FTP"); break;
        case 22:   Serial.println("SSH"); break;
        case 23:   Serial.println("Telnet ⚠️"); break;
        case 25:   Serial.println("SMTP"); break;
        case 53:   Serial.println("DNS"); break;
        case 80:   Serial.println("HTTP"); break;
        case 443:  Serial.println("HTTPS"); break;
        case 445:  Serial.println("SMB"); break;
        case 3306: Serial.println("MySQL"); break;
        case 3389: Serial.println("RDP"); break;
        case 5000: Serial.println("UPnP"); break;
        case 8080: Serial.println("HTTP-Alt"); break;
        case 8888: Serial.println("HTTP-Alt"); break;
        default:   Serial.println("Unknown");
      }
      
      client.stop();
      
      // Blink LED
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      
    } else {
      Serial.printf("%-8d closed\n", port);
    }
    
    delay(100); // Small pause between scans
  }
  
  // Summary
  Serial.println("\n╔═══════════════════════════════════════╗");
  Serial.println("║          SCAN SUMMARY                ║");
  Serial.println("╠═══════════════════════════════════════╣");
  Serial.printf("║ Ports scanned: %-22d║\n", numPorts);
  Serial.printf("║ Open ports: %-25d║\n", openPorts);
  Serial.printf("║ Closed ports: %-23d║\n", numPorts - openPorts);
  Serial.println("╚═══════════════════════════════════════╝\n");
  
  // Security recommendations
  if (openPorts > 0) {
    Serial.println("⚠️ SECURITY RECOMMENDATIONS:");
    Serial.println("  • Close unused ports");
    Serial.println("  • Use firewall to protect services");
    Serial.println("  • Keep software updated");
    Serial.println("  • Use strong passwords");
    
    if (client.connect(ipStr.c_str(), 23, 1000)) {
      Serial.println("  • ⚠️ Telnet is INSECURE, use SSH instead");
      client.stop();
    }
  } else {
    Serial.println("✓ No common open ports detected");
    Serial.println("  This may indicate good security level");
  }
  
  // Disconnect WiFi
  WiFi.disconnect();
  Serial.println("\nDisconnected from WiFi network");
}
