# 🌐 PlatformIO Project: T-IOT-902

This project is built for the **Heltec WiFi LoRa 32 V2** board using **PlatformIO**.  
It connects to WiFi, displays real-time logs on the built-in **OLED screen**, and uploads sensor data to [Sensor.Community](https://sensor.community/).

---

## 📋 Features

-  📡 Automatic WiFi connection
-  🌍 Sends temperature/humidity data to Sensor.Community
-  📺 Displays logs in real-time on the OLED screen
-  ⚙️ Clean modular PlatformIO structure
-  💡 Logs simultaneously to Serial and OLED
-  🔄 Includes GitHub Actions CI for firmware packaging and release

---

## 🧱 Project Architecture

```
├── include/
│   ├── variables.hpp            # 🔐 Not tracked – contains credentials
│   ├── wifi_manager.h           # WiFi connection utility
│   ├── sensor_api.hpp           # Sensor.Community HTTP client
│   └── display_manager.hpp      # OLED logging abstraction
├── src/
│   ├── main.cpp
│   ├── wifi_manager.cpp
│   ├── sensor_api.cpp
│   └── display_manager.cpp
├── .github/
│   └── workflows/
│       └── tag-and-release.yml  # GitHub Actions workflow
├── .gitignore
├── platformio.ini
└── README.md
```

---

## 📦 Dependencies

Declared in `platformio.ini`:

```ini
lib_deps =
  sandeepmistry/LoRa @ ^0.8.0
  heltecautomation/Heltec ESP32 Dev-Boards @ 1.1.2
```

> 🧠 Uses the Heltec library for managing the OLED and board-specific setup.

---

## 🔧 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/your-username/your-repo.git
cd your-repo
```

### 2. Create your `variables.hpp`

> ⚠️ This file is ignored by Git and required for WiFi setup.

```cpp
#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#define WIFI_SSID "your-ssid"
#define WIFI_PASSWORD "your-password"

#endif
```

Or copy a pre-made template:

```bash
cp include/variables.template.hpp include/variables.hpp
```

### 3. Build and flash the firmware

```bash
# Compile
platformio run

# Upload to the ESP32
platformio run --target upload
```

---

## 🧪 Test Payload with `curl`

Simulate a real HTTP POST like the ESP32 does:

```bash
curl -X POST https://api.sensor.community/v1/push-sensor-data/ \
  -H "Content-Type: application/json" \
  -H "X-Sensor: esp32-heltec-mar-2" \
  -d '{
    "sensordatavalues": [
      { "value_type": "temperature", "value": "23.4" }
    ]
  }'
```

Make sure:

-  You replace `X-Sensor` with your **actual registered device ID**
-  The payload matches the sensor types you've configured

---

## 🖥️ OLED Logging

OLED messages are managed by a rotating buffer, showing 6 latest messages like a mini-terminal:

```cpp
DisplayManager::log("Connecting...");
DisplayManager::log("WiFi OK");
DisplayManager::log("Sending payload...");
```

All messages are shown:

-  On the OLED screen
-  On the Serial Monitor (115200 baud)

---

## 🔄 Continuous Integration (CI/CD)

This repo includes a GitHub Actions workflow:

-  Auto-tags versions (major/minor/patch via commit messages)
-  Builds using PlatformIO in CI
-  Uploads binaries and manifest
-  Generates a release ZIP with flashing instructions

See `.github/workflows/tag-and-release.yml` for details.

---

## 🔐 Environment Separation

-  `variables.hpp` is **excluded from git** for security
-  Can be dynamically generated in CI using `variables.template.hpp` or secrets

---

## 🙋 Author

Built by **Nacer, Amine and Mattéo** for open-source IoT experimentation.  
Inspired by [Sensor.Community](https://sensor.community/) and the power of ESP32 boards.

> Feedback and contributions welcome!
