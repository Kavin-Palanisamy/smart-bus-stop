# 🚌 Smart Bus Stop IoT Display System

An IoT-based Smart Bus Stop Display System built using **ESP8266 NodeMCU, Firebase Realtime Database and 16×2 I2C LCD displays**.

The system retrieves bus information from Firebase through Wi-Fi and displays current bus timings, delay information and upcoming buses automatically.

--

## 📌 Project Overview

Traditional bus stops often provide limited or no real-time information about bus arrivals and delays.

This project provides a low-cost IoT solution where bus information is stored in a Firebase Realtime Database and displayed dynamically on LCD screens installed at bus stops.

The system can display:

* Current bus number
* Bus route
* Scheduled arrival time
* Delay status
* Actual expected arrival time when delayed
* Upcoming buses
* 12-hour AM/PM time format

---

## ✨ Features

* 📡 Wi-Fi connectivity using ESP8266
* ☁️ Firebase Realtime Database integration
* 🚌 Real-time bus information
* ⏰ 12-hour AM/PM display
* ⚠️ Delay indication
* 🔄 Automatic data refresh
* ➡️ Smooth LCD scrolling
* 🚌 Upcoming bus display
* 🖥️ Dual LCD support for two bus stops
* 🔁 Automatic switching between current and upcoming buses
* 💻 Low-cost embedded IoT implementation

---

## 🛠️ Hardware

| Component        |    Quantity |
| ---------------- | ----------: |
| ESP8266 NodeMCU  |           1 |
| 16×2 I2C LCD     |           2 |
| Jumper Wires     | As required |
| Breadboard       |           1 |
| USB Power Supply |           1 |
| Wi-Fi Network    |           1 |

---

## 💻 Software

* Arduino IDE
* ESP8266 Board Package
* Firebase ESP Client Library
* LiquidCrystal_I2C Library
* Firebase Realtime Database

---

## 🔌 Hardware Connections

### LCD 1 — Stop 1

| LCD | ESP8266  |
| --- | -------- |
| VCC | VIN / 5V |
| GND | GND      |
| SDA | D2       |
| SCL | D1       |

### LCD 2 — Stop 2

Both LCDs share the same I2C bus.

| LCD | ESP8266  |
| --- | -------- |
| VCC | VIN / 5V |
| GND | GND      |
| SDA | D2       |
| SCL | D1       |

The two LCDs use different I2C addresses:

```text
LCD 1 → 0x27
LCD 2 → 0x26
```

---

## 🧠 System Architecture

```text
                ┌─────────────────────┐
                │   Firebase RTDB      │
                │                     │
                │ Bus Number           │
                │ Route                │
                │ Time                 │
                │ Delay                │
                └──────────┬──────────┘
                           │
                           │ Internet
                           ▼
                  ┌─────────────────┐
                  │    ESP8266      │
                  │   NodeMCU       │
                  └────────┬────────┘
                           │
                     I2C Communication
                    ┌──────┴──────┐
                    ▼             ▼
              ┌──────────┐   ┌──────────┐
              │ LCD Stop1│   │ LCD Stop2│
              │  0x27    │   │  0x26    │
              └──────────┘   └──────────┘
```

---

## 🔥 Firebase Database Structure

The project uses a structure similar to:

```text
smart_bus_stop
│
└── buses
    │
    ├── bus_23
    │   ├── route
    │   └── stops
    │       ├── stop1
    │       │   ├── time
    │       │   └── delay
    │       └── stop2
    │           ├── time
    │           └── delay
    │
    ├── bus_45
    │
    ├── bus_78
    │
    └── bus_115
```

Example:

```text
bus_78
├── route: "Chennai-DGL"
└── stops
    └── stop1
        ├── time: "15:30"
        └── delay: 5
```

---

## 📺 Display Example

### Current Bus

```text
Bus 78 Chennai-DGL
Delay +5 min 03:35 PM
```

### On-Time Bus

```text
Bus 115 Chennai-DGL
On Time
```

### Upcoming Bus

```text
Next Bus 115 Chennai-DGL
Upcoming
```

The first line scrolls horizontally while the second line remains static when showing the "Upcoming" or "On Time" status.

---

## ⏰ Time Format

Bus schedules are stored in the database using 24-hour format:

```text
15:30
```

The ESP8266 converts the time to 12-hour format for display:

```text
03:30 PM
```

For delayed buses:

```text
Delay +5 min 03:35 PM
```

---

## 🔄 System Operation

1. ESP8266 starts.
2. ESP8266 connects to the configured Wi-Fi network.
3. Firebase connection is initialized.
4. NTP time synchronization is performed.
5. Bus data is retrieved from Firebase.
6. The system identifies the next available bus.
7. Current bus information is displayed.
8. Upcoming buses are stored for display.
9. The LCD scrolls long bus information smoothly.
10. The system periodically displays upcoming buses.
11. Firebase data is refreshed automatically.
12. The process repeats continuously.

---

## 📁 Project Structure

```text
smart-bus-stop-iot/
│
├── firmware/
│   └── smart_bus_stop/
│       └── smart_bus_stop.ino
│
├── docs/
│   ├── circuit-diagram.png
│   ├── system-architecture.png
│   └── project-images/
│
├── README.md
├── .gitignore
└── LICENSE
```

---

## 🚀 Getting Started

### 1. Install Arduino IDE

Install Arduino IDE and configure the ESP8266 board package.

### 2. Select Board

In Arduino IDE:

```text
Tools
→ Board
→ ESP8266 Boards
→ NodeMCU 1.0 (ESP-12E Module)
```

### 3. Install Required Libraries

Install:

```text
Firebase ESP Client
LiquidCrystal_I2C
```

The ESP8266 Wi-Fi, Wire and time libraries are provided by the ESP8266 environment.

### 4. Configure Firebase

Create a Firebase Realtime Database and create the required database structure.

### 5. Configure Credentials

Before uploading the firmware, replace the placeholder values:

```cpp
#define WIFI_SSID     "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define DATABASE_URL  "YOUR_FIREBASE_DATABASE_URL"
#define DATABASE_SECRET "YOUR_FIREBASE_SECRET"
```

**Do not publish real passwords or database secrets.**

### 6. Upload Firmware

Open:

```text
firmware/smart_bus_stop/smart_bus_stop.ino
```

Select the NodeMCU board and correct COM port, then upload.

---

## ⚙️ Configuration

The buses currently configured in the firmware are:

```cpp
String buses[] = {
  "bus_23",
  "bus_45",
  "bus_78",
  "bus_115"
};
```

The number of upcoming buses can be controlled using:

```cpp
#define MAX_UPCOMING 4
```

LCD addresses:

```cpp
LCD 1 → 0x27
LCD 2 → 0x26
```

Scroll speed can be adjusted in the `runScroll()` function.

---

## 🔐 Security

Never commit the following information to a public GitHub repository:

* Wi-Fi password
* Firebase secret
* API keys
* Private tokens
* Authentication credentials

Use placeholders in the public firmware.

If credentials have already been exposed, revoke or rotate them before publishing the repository.

---

## 🔮 Future Improvements

Possible future versions could include:

* GPS-based live bus tracking
* Mobile application
* Web dashboard
* Automatic bus location tracking
* Google Maps integration
* Voice announcements
* LED matrix display
* Multiple bus-stop support
* Cloud-based administration panel
* Estimated Time of Arrival prediction
* Traffic-aware arrival prediction
* QR code for passenger information

---

## 🎯 Applications

This system can be adapted for:

* Smart bus stops
* College transportation
* School transportation
* Smart city projects
* Public transport terminals
* Corporate shuttle systems
* Railway/metro feeder services

---

## 👨‍💻 Project Type

**IoT + Embedded Systems + Cloud**

---

## 📜 License

This project is licensed under the MIT License.

---

## ⭐ Project Goal

The goal of this project is to demonstrate how **IoT, embedded systems and cloud technology** can be combined to create a practical smart transportation solution.
