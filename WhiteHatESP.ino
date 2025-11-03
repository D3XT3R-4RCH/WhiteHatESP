/*
 * White Hat ESP32 - Defensive Cybersecurity Tools
 * Educational project to learn about WiFi security
 * 
 * Created by: D3XT3R-4RCH
 * 
 * WARNING: For educational use only and on your own networks
 */

#include "WiFi.h"
#include "esp_wifi.h"

// LED pin for alerts (optional)
#define LED_PIN 2

// Global variables
int menuOption = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Welcome message with ASCII Art
  Serial.println("\n\n");
  Serial.println(" __      __.__    .__  __             ___ ___         __    ___________ ___________________  ________  ________  ");
  Serial.println("/  \\    /  \\  |__ |__|/  |_  ____    /   |   \\_____ _/  |_  \\_   _____//   _____/\\______   \\ \\_____  \\ \\_____  \\ ");
  Serial.println("\\   \\/\\/   /  |  \\|  \\   __\\/ __ \\  /    ~    \\__  \\\\   __\\  |    __)_ \\_____  \\  |     ___/   _(__  <  /  ____/ ");
  Serial.println(" \\        /|   Y  \\  ||  | \\  ___/  \\    Y    // __ \\|  |    |        \\/        \\ |    |      /       \\/       \\ ");
  Serial.println("  \\__/\\  / |___|  /__||__|  \\___  >  \\___|_  /(____  /__|   /_______  /_______  / |____|     /______  /\\_______ \\");
  Serial.println("       \\/       \\/              \\/         \\/      \\/               \\/        \\/                    \\/         \\/");
  Serial.println();
  Serial.println("════════════════════════════════════════════════════════════════════════════════════════════════════════════════");
  Serial.println("                              🛡️  DEFENSIVE SECURITY TOOLS 🛡️                                                  ");
  Serial.println("════════════════════════════════════════════════════════════════════════════════════════════════════════════════");
  Serial.println("  Educational Cybersecurity Project | Version 1.0 | Created by: D3XT3R-4RCH");
  Serial.println();
  Serial.println("  ⚠️  LEGAL WARNING:");
  Serial.println("      • For educational use only");
  Serial.println("      • Use ONLY on your own networks");
  Serial.println("      • Unauthorized use is ILLEGAL");
  Serial.println();
  Serial.println("  📚 Learn about: WiFi Security • Network Analysis • Ethical Hacking • Defensive Security");
  Serial.println("════════════════════════════════════════════════════════════════════════════════════════════════════════════════");
  Serial.println();
  
  showMenu();
}

void loop() {
  if (Serial.available() > 0) {
    menuOption = Serial.parseInt();
    
    if (menuOption >= 1 && menuOption <= 5) {
      executeTool(menuOption);
      delay(2000);
      showMenu();
    }
  }
}

void showMenu() {
  Serial.println("\n========================================");
  Serial.println("           MAIN MENU");
  Serial.println("========================================");
  Serial.println("1. WiFi Security Scanner");
  Serial.println("2. Deauth Detection & Alert");
  Serial.println("3. Network Packet Monitor");
  Serial.println("4. Evil Twin Detector");
  Serial.println("5. Port Scanner");
  Serial.println("========================================");
  Serial.println("Enter the tool number:");
}

void executeTool(int option) {
  Serial.println("\n========================================");
  
  switch(option) {
    case 1:
      wifiSecurityScanner();
      break;
    case 2:
      deauthDetection();
      break;
    case 3:
      packetMonitor();
      break;
    case 4:
      evilTwinDetector();
      break;
    case 5:
      portScanner();
      break;
    default:
      Serial.println("Invalid option");
  }
  
  Serial.println("========================================");
  Serial.println("Press Enter to return to menu...");
  while(Serial.available()) Serial.read(); // Clear buffer
}
