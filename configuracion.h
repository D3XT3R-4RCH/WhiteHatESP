/*
 * Configuration file for White Hat ESP
 * Customize tool behavior here
 * Created by: D3XT3R-4RCH
 */

#ifndef CONFIGURACION_H
#define CONFIGURACION_H

// ========================================
// HARDWARE CONFIGURATION
// ========================================

// Alert LED pin (change according to your ESP32)
// GPIO2 is the built-in LED on most ESP32
// #define LED_PIN 2  // Already defined in main file

// ========================================
// DETECTION CONFIGURATION
// ========================================

// Deauth packet threshold to consider an attack
// Typical values: 10-50 packets
#define DEAUTH_THRESHOLD 10

// Scan time per channel (milliseconds)
#define TIME_PER_CHANNEL 2000

// ========================================
// PORT SCANNER CONFIGURATION
// ========================================

// Port connection timeout (milliseconds)
#define PORT_TIMEOUT 1000

// Additional ports to scan (customize as needed)
// const int commonPorts[] = {...}  // Defined in tool5

// ========================================
// MONITOR CONFIGURATION
// ========================================

// Statistics update interval (seconds)
#define STATS_INTERVAL 5

// Management packet percentage for alert
#define MGMT_THRESHOLD_PERCENT 0.5

// ========================================
// SERIAL CONFIGURATION
// ========================================

// Serial monitor speed
#define BAUD_RATE 115200

// ========================================
// CUSTOMIZABLE MESSAGES
// ========================================

#define PROJECT_NAME "WHITE HAT ESP"
#define VERSION "1.0"
#define AUTHOR "D3XT3R-4RCH"

#endif
