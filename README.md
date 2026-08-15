# 🚌 Smart Bus Stop

An IoT-based Smart Bus Stop system that provides passengers with real-time bus information through an LCD display. The system uses an **ESP8266** to connect to the internet and retrieve bus information from **Firebase Realtime Database**.

---

## 📌 Overview

Traditional bus stops often provide only static information about bus routes and timings. Passengers may not know whether a bus is on time, delayed, or approaching.

The **Smart Bus Stop** aims to improve the passenger experience by providing dynamically updated bus information at the bus stop.

The ESP8266 connects to Firebase through Wi-Fi, retrieves the available bus information, and displays it on an LCD. The display automatically rotates between different buses.

---

## 🎯 Problem Statement

Passengers at conventional bus stops may face difficulties such as:

* Uncertainty about bus timings
* No information about delays
* Dependence on static timetables
* Difficulty tracking multiple buses

---

## 💡 Proposed Solution

The Smart Bus Stop uses IoT technology to provide dynamic bus information.

```text
             ┌─────────────────────┐
             │   Firebase Database  │
             │                     │
             │ Bus Number          │
             │ Route               │
             │ Timing              │
             │ Status              │
             │ Delay               │
             └──────────┬──────────┘
                        │
                     Internet
                        │
                        ▼
             ┌─────────────────────┐
             │      ESP8266        │
             │  Wi-Fi Controller   │
             └──────────┬──────────┘
                        │
                        ▼
             ┌─────────────────────┐
             │     LCD Display     │
             │                     │
             │ Bus No. / Route     │
             │ Timing / Status     │
             └─────────────────────┘
```

---

## 🚀 Features

* 📡 Wi-Fi connectivity using ESP8266
* ☁️ Firebase Realtime Database integration
* 🚌 Bus number and route display
* 🕐 Bus timing display
* ⚠️ Delay/status indication
* 🔄 Automatic rotation between buses
* 📟 LCD-based passenger information display
* 🌐 Cloud-based bus information management

---

## 🛠️ Hardware Components

| Component      | Purpose                                 |
| -------------- | --------------------------------------- |
| ESP8266        | Main controller and Wi-Fi communication |
| LCD Display    | Displays bus information                |
| I2C LCD Module | Communication between ESP8266 and LCD   |
| Breadboard     | Circuit prototyping                     |
| Jumper Wires   | Component connections                   |
| Power Supply   | Provides power to the system            |

> Update this table if your final hardware setup contains additional components.

---

## 💻 Software & Technologies

* **Arduino IDE**
* **C/C++**
* **ESP8266**
* **Firebase Realtime Database**
* **Wi-Fi**

---

## 🔄 Working Principle

The system works in the following sequence:

1. Bus information is stored in Firebase Realtime Database.
2. The ESP8266 connects to the available Wi-Fi network.
3. The ESP8266 establishes communication with Firebase.
4. Bus information is retrieved from the database.
5. The received data is processed by the ESP8266.
6. Bus number, route, timing, and status are displayed on the LCD.
7. The LCD automatically rotates through the available buses.
8. When a bus is delayed, the corresponding delay/status information can be displayed.

---

## 📟 LCD Display

The LCD is used to provide passengers with simple and readable information.

Example:

```text
BUS: 12A
DINDIGUL-PALANI
```

or

```text
BUS: 15
DELAY: 10 MIN
```

The display can automatically change between different buses.

---


## ⚙️ Installation & Setup

### 1. Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/smart-bus-stop.git
```

```bash
cd smart-bus-stop
```

### 2. Install Arduino IDE

Install the Arduino IDE and configure the ESP8266 board package.

### 3. Connect the Hardware

Connect the ESP8266 to the LCD according to the circuit diagram provided in the `circuit` folder.

### 4. Configure Wi-Fi

Open the firmware file and enter your Wi-Fi credentials.

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

### 5. Configure Firebase

Add the required Firebase configuration using placeholder values or a separate local configuration file.

**Do not upload real passwords, tokens, or private credentials to GitHub.**

### 6. Upload the Firmware

Select the appropriate ESP8266 board and COM port in Arduino IDE and upload the firmware.

### 7. Monitor the System

Open the Serial Monitor to check:

* Wi-Fi connection
* Firebase connection
* Retrieved bus information
* System status

---


## 📈 Future Improvements

The project can be further developed with:

* 📍 GPS-based bus tracking
* 🗺️ Real-time bus location
* 📱 Mobile application
* 🔔 Passenger notifications
* 🖥️ Larger LED/LCD display
* 🎙️ Voice announcements for visually impaired passengers
* 📊 Web-based administration dashboard
* 🤖 AI-based arrival time prediction
* 🌐 Multiple bus-stop synchronization
* 📶 Offline data caching
* 🔋 Solar-powered bus stop system

---

## 🌍 Potential Applications

The concept can be extended to:

* Smart cities
* Public transportation systems
* College campuses
* Railway/bus terminals
* Rural transportation networks
* Government transport systems

---


## 📚 Learning Outcomes

Through this project, the following concepts were explored:

* IoT system development
* ESP8266 programming
* Wi-Fi communication
* Firebase Realtime Database
* LCD interfacing
* Cloud-connected embedded systems
* Real-time data handling
* Hardware and software integration
* Git and GitHub project management

---

## 👨‍💻 Author

**Kavin**

Electrical and Electronics Engineering Student

Interested in:

* IoT
* Embedded Systems
* Cloud Technologies
* AI + IoT

---

## ⭐ Support

If you find this project useful or interesting, consider giving the repository a ⭐ on GitHub.

---

## 📜 License

This project is open-source and available for educational and learning purposes.
