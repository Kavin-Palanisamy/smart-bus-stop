# Smart Bus Stop - Project Documentation

## 1. Project Overview

The Smart Bus Stop is an IoT-based bus information display system.
It uses NodeMCU ESP8266, I2C LCD displays and Firebase Realtime Database
to display real-time bus arrival information.

## 2. Main Features

- Real-time bus information
- Firebase-based data management
- Automatic bus scheduling
- 12-hour time format
- Delay indication
- Upcoming bus information
- Automatic scrolling display
- Multiple LCD displays
- Wi-Fi connectivity

## 3. Hardware

- NodeMCU ESP8266
- 16x2 I2C LCD × 2
- Power supply
- Connecting wires

## 4. Software

- Arduino IDE
- ESP8266 Board Package
- Firebase
- LiquidCrystal_I2C Library

## 5. Communication

NodeMCU communicates with Firebase through Wi-Fi.

The LCD displays communicate with the NodeMCU using the I2C protocol.

## 6. LCD Addresses

LCD 1: 0x27

LCD 2: 0x26

## 7. I2C Connections

D2 (GPIO4) → SDA

D1 (GPIO5) → SCL

GND → GND

VCC → VCC

## 8. Working

1. NodeMCU connects to Wi-Fi.
2. NodeMCU connects to Firebase.
3. Bus information is retrieved from Firebase.
4. Current time is obtained using NTP.
5. Bus arrival times are compared with the current time.
6. The next available bus is selected.
7. Bus information is displayed on the LCD.
8. Upcoming buses are displayed periodically.
9. Bus information automatically scrolls across the LCD.
10. Data is refreshed periodically from Firebase.

## 9. Display Format

Current bus:

Bus 78 Chennai-DGL 03:30 PM

On Time

If delayed:

Bus 78 Chennai-DGL 03:30 PM

Delay +5 min 03:35 PM

Upcoming bus:

Next Bus 115 Chennai-DGL 04:00 PM

Upcoming

## 10. Future Improvements

- GPS-based bus tracking
- Mobile application
- Voice announcements
- More bus stops
- Real-time bus location
- Cloud-based analytics
- Emergency notifications
