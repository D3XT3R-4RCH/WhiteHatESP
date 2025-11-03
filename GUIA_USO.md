# Guía de Uso - White Hat ESP

## 🚀 Inicio Rápido

### 1. Conexión del ESP32
1. Conecta tu ESP32 a la computadora vía USB
2. Abre Arduino IDE
3. Abre el archivo `WhiteHatESP.ino`
4. Selecciona tu placa: `Tools -> Board -> ESP32 Dev Module`
5. Selecciona el puerto COM correcto: `Tools -> Port -> COMx`
6. Click en "Upload" (→)

### 2. Abrir Monitor Serial
1. Click en `Tools -> Serial Monitor`
2. Configura velocidad: **115200 baud**
3. Verás el menú principal

---

## 🛠️ Descripción de Herramientas

### 📡 Herramienta 1: WiFi Security Scanner

**¿Qué hace?**
- Escanea todas las redes WiFi cercanas
- Muestra tipo de encriptación
- Detecta redes inseguras (abiertas o con WEP)

**Cómo usar:**
1. Escribe `1` en el monitor serial
2. Espera a que termine el escaneo (10-20 segundos)
3. Revisa el reporte de seguridad

**¿Qué aprendes?**
- Tipos de encriptación WiFi (WEP, WPA, WPA2, WPA3)
- Cómo identificar redes vulnerables
- Importancia de usar WPA2/WPA3

**Interpretación:**
- ⚠️ ABIERTA = Sin contraseña, cualquiera puede conectarse
- ⚠️ WEP = Obsoleta, se hackea en minutos
- ⚠️ WPA = Vulnerable a ataques
- ✓ WPA2 = Segura para uso doméstico
- ✓✓ WPA3 = Máxima seguridad actual

---

### 🛡️ Herramienta 2: Deauth Detection & Alert

**¿Qué hace?**
- Detecta ataques de deautenticación
- Monitorea todos los canales WiFi
- Alerta si hay actividad sospechosa

**Cómo usar:**
1. Escribe `2` en el monitor serial
2. El ESP32 comenzará a monitorear
3. Presiona `s` para detener

**¿Qué aprendes?**
- Cómo funcionan los ataques de deauth
- Packets management de WiFi
- Detección de amenazas en tiempo real

**¿Cuándo alertará?**
- Si detecta más de 10 paquetes deauth (configurable)
- El LED parpadeará rápidamente
- Verás mensaje de alerta en serial

**Nota:** Los paquetes deauth también ocurren naturalmente cuando dispositivos se desconectan.

---

### 📊 Herramienta 3: Network Packet Monitor

**¿Qué hace?**
- Captura y analiza tráfico WiFi
- Muestra estadísticas en tiempo real
- Detecta patrones anormales

**Cómo usar:**
1. Escribe `3` en el monitor serial
2. Observa las estadísticas cada 5 segundos
3. Presiona `s` para detener

**¿Qué aprendes?**
- Tipos de paquetes WiFi (Management, Control, Data)
- Análisis de tráfico de red
- Modo promiscuo del WiFi

**Interpretación:**
- **Management**: Gestión de conexiones (beacons, probes)
- **Control**: Control de flujo (ACK, RTS/CTS)
- **Data**: Datos de usuario

**Alerta:** Alto porcentaje de Management puede indicar escaneos o ataques.

---

### 👥 Herramienta 4: Evil Twin Detector

**¿Qué hace?**
- Detecta puntos de acceso falsos
- Identifica SSIDs duplicados
- Compara direcciones MAC

**Cómo usar:**
1. Escribe `4` en el monitor serial
2. Espera el análisis automático
3. Revisa alertas de SSIDs duplicados

**¿Qué aprendes?**
- Qué es un ataque Evil Twin
- Importancia de verificar direcciones MAC
- Cómo protegerte de redes falsas

**Evil Twin:** Cuando un atacante crea una red WiFi falsa con el mismo nombre que una legítima para robar datos.

**Recomendación:** Anota la MAC de tu router real para futuras comparaciones.

---

### 🔍 Herramienta 5: Port Scanner

**¿Qué hace?**
- Escanea puertos abiertos en dispositivos
- Identifica servicios expuestos
- Detecta vulnerabilidades potenciales

**Cómo usar:**
1. Escribe `5` en el monitor serial
2. Ingresa SSID de tu red WiFi
3. Ingresa la contraseña
4. Ingresa IP a escanear (o Enter para el gateway)
5. Revisa puertos abiertos

**¿Qué aprendes?**
- Qué son los puertos de red
- Servicios comunes (HTTP, SSH, FTP, etc.)
- Importancia de cerrar puertos innecesarios

**Puertos importantes:**
- **22 (SSH)**: Acceso remoto seguro
- **23 (Telnet)**: ⚠️ Acceso remoto INSEGURO
- **80 (HTTP)**: Servidor web sin cifrar
- **443 (HTTPS)**: Servidor web cifrado
- **3389 (RDP)**: Escritorio remoto Windows

---

## ⚠️ Advertencias de Seguridad

### Legal
- ✅ **USA solo en TU red**
- ❌ **NO escanees redes de terceros sin permiso**
- ❌ **NO uses para atacar o dañar**
- ⚖️ El uso no autorizado es ILEGAL

### Ético
Este proyecto es para:
- ✓ Aprendizaje educativo
- ✓ Proteger tu propia red
- ✓ Entender vulnerabilidades
- ✓ Mejorar tu seguridad

NO para:
- ✗ Hackear redes ajenas
- ✗ Robar información
- ✗ Causar daño

---

## 🐛 Solución de Problemas

### No compila el código
- Verifica que tienes el soporte ESP32 instalado
- Ve a `File -> Preferences -> Additional Board Manager URLs`
- Agrega: `https://dl.espressif.com/dl/package_esp32_index.json`
- Ve a `Tools -> Board -> Boards Manager`, busca "ESP32" e instala

### No se conecta al WiFi (Herramienta 5)
- Verifica SSID y contraseña
- Asegúrate de estar en rango
- Tu red debe ser 2.4GHz (ESP32 no soporta 5GHz)

### No detecta ataques
- Normal si tu red está segura
- Puedes probar con herramientas legítimas de auditoría
- Solo con TU red y con fines educativos

### LED no parpadea
- Verifica que el pin del LED es correcto
- En `WhiteHatESP.ino` cambia `#define LED_PIN 2`
- Algunos ESP32 usan GPIO diferente

---

## 📚 Recursos Adicionales

### Para Aprender Más
- **WiFi Security**: Busca sobre WPA3, 802.11w (PMF)
- **Network Protocols**: Estudia TCP/IP, OSI model
- **Ethical Hacking**: Cursos de ciberseguridad ética

### Herramientas Complementarias
- **Wireshark**: Análisis de paquetes avanzado
- **Nmap**: Port scanner profesional
- **aircrack-ng**: Suite de auditoría WiFi

---

## 🔄 Próximas Mejoras

Ideas para expandir el proyecto:
- [ ] Almacenamiento de logs en SD
- [ ] Interfaz web
- [ ] Integración con Telegram/Discord
- [ ] GPS para geo-localización
- [ ] Pantalla OLED para visualización
- [ ] Detección de Bluetooth

---

## 💡 Tips y Consejos

1. **Portabilidad**: Agrega una batería para hacerlo portable
2. **Logs**: Conecta módulo SD para guardar resultados
3. **Visualización**: Agrega pantalla OLED para ver sin PC
4. **Alertas**: Implementa buzzer para alertas sonoras
5. **Automatización**: Programa escaneos periódicos

---

¿Preguntas? ¡Experimenta y aprende! 🚀
