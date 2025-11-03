# White Hat ESP - Herramientas de Ciberseguridad Defensiva

Proyecto educativo de ciberseguridad defensiva para ESP32.

## 🛡️ Herramientas Incluidas

### 1. WiFi Security Scanner
Escanea redes WiFi cercanas y detecta configuraciones inseguras.
- Detecta tipo de encriptación (WEP, WPA, WPA2, WPA3)
- Identifica redes sin contraseña
- Muestra intensidad de señal (RSSI)

### 2. Deauth Detection & Alert
Monitorea y detecta ataques de deautenticación en redes WiFi.
- Detecta paquetes de deautenticación
- Sistema de alertas con LED y serial
- Útil para proteger tu red

### 3. Network Packet Monitor
Analiza el tráfico WiFi en tiempo real.
- Modo monitor/promiscuo
- Estadísticas de paquetes
- Detección de patrones anormales

### 4. Evil Twin Detector
Detecta puntos de acceso falsos o duplicados.
- Identifica SSIDs duplicados
- Compara direcciones MAC
- Alertas de redes sospechosas

### 5. Port Scanner
Escanea puertos abiertos en dispositivos de la red local.
- Escaneo de puertos comunes
- Detección de servicios
- Mapeo de red local

## 📋 Requisitos

### Hardware
- ESP32 (cualquier modelo)
- LED (opcional, para alertas visuales)
- Resistencia 220Ω (para el LED)

### Software
- Arduino IDE 2.0+ o PlatformIO
- Librerías necesarias (se instalan automáticamente)

## 🔧 Instalación

1. Clona o descarga este repositorio
2. Abre el archivo `WhiteHatESP.ino` en Arduino IDE
3. Selecciona tu placa ESP32 en Tools -> Board
4. Selecciona el puerto COM correcto
5. Sube el código

## 🚀 Uso

1. Conecta el ESP32 a tu computadora
2. Abre el Monitor Serial (115200 baudios)
3. Verás el menú principal con las 5 herramientas
4. Escribe el número de la herramienta que quieres usar
5. Sigue las instrucciones en pantalla

## ⚠️ Advertencia Legal

Este proyecto es SOLO para fines educativos y de seguridad defensiva.
- Solo escanea TU propia red
- No uses estas herramientas para atacar redes de terceros
- El uso malicioso es ilegal y éticamente incorrecto
- El autor no se responsabiliza por el mal uso de este código

## 📚 Propósito Educativo

Este proyecto te ayudará a entender:
- Cómo funcionan las redes WiFi
- Vulnerabilidades comunes en seguridad
- Técnicas de defensa y monitoreo
- Programación de ESP32
- Conceptos de ciberseguridad

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Siéntete libre de mejorar el código y agregar nuevas herramientas.

## 📄 Licencia

Este proyecto es de código abierto para fines educativos.
