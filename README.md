# White Hat ESP — Defensive Cybersecurity Tools

An educational defensive cybersecurity project for the ESP32.

## 🛡️ Included Tools

### 1. WiFi Security Scanner
Scans nearby WiFi networks and highlights insecure configurations.
- Detects encryption type (WEP, WPA, WPA2, WPA3)
- Identifies open (password-less) networks
- Shows signal strength (RSSI)

### 2. Deauth Detection & Alert
Monitors and detects deauthentication attacks on WiFi networks.
- Detects deauthentication packets
- Alert system using LED and Serial output
- Useful to help protect your network

### 3. Network Packet Monitor
Analyzes WiFi traffic in real time.
- Monitor/promiscuous mode
- Packet statistics
- Detection of unusual patterns

### 4. Evil Twin Detector
Detects fake or duplicated access points.
- Identifies duplicate SSIDs
- Compares BSSID (MAC) addresses
- Alerts for suspicious networks

### 5. Port Scanner
Scans for open ports on devices in the local network.
- Scans common ports
- Attempts basic service identification
- Helps map local network devices

## 📋 Requirements

### Hardware
- ESP32 (any model)
- LED (optional, for visual alerts)
- 220Ω resistor (for the LED)

### Software
- Arduino IDE 2.0+ or PlatformIO
- Required libraries (should install automatically when compiling)

## 🔧 Installation

1. Clone or download this repository
2. Open `WhiteHatESP.ino` in the Arduino IDE
3. Select your ESP32 board in Tools -> Board
4. Select the correct COM port
5. Upload the sketch to the board

## 🚀 Usage

1. Connect the ESP32 to your computer
2. Open the Serial Monitor at 115200 baud
3. You will see the main menu listing the 5 tools
4. Enter the number of the tool you want to run
5. Follow the on-screen instructions

## ⚠️ Legal Warning

This project is ONLY for educational and defensive security purposes.
- Only scan YOUR own network
- Do not use these tools to attack third-party networks
- Malicious use is illegal and unethical
- The author is not responsible for misuse of this code

## 📚 Educational Purpose

This project will help you learn:
- How WiFi networks work
- Common security weaknesses
- Defense and monitoring techniques
- ESP32 programming
- Cybersecurity fundamentals

## 🤝 Contributions

Contributions are welcome! Feel free to improve the code and add new tools.

## 📄 License

This project is open source for educational purposes.
