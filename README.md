# Smart Irrigation System using ESP32

## Project Overview

The Smart Irrigation System is an IoT-based agricultural project developed using ESP32. The system monitors environmental conditions such as temperature, humidity, and soil moisture and provides remote control of the irrigation pump through a web-based interface.

The project aims to improve irrigation efficiency, reduce water wastage, and support smart agriculture using embedded systems and IoT technologies.

## Features

- Soil moisture monitoring
- Temperature monitoring using DHT11
- Humidity monitoring using DHT11
- Water pump control using a relay
- 16x2 I2C LCD display
- ESP32 Wi-Fi connectivity
- Web-based monitoring interface
- Remote pump ON/OFF control
- Real-time sensor data display

## Hardware Components

- ESP32 Development Board
- DHT11 Temperature and Humidity Sensor
- Soil Moisture Sensor
- Relay Module
- Water Pump
- 16x2 I2C LCD
- Jumper Wires
- Breadboard
- Power Supply

## Pin Configuration

| Component | ESP32 Pin |
|-----------|-----------|
| DHT11 | GPIO 14 |
| Soil Moisture Sensor | GPIO 27 |
| Relay | GPIO 26 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |

## Software and Technologies

- Arduino IDE
- Embedded C/C++
- ESP32
- Wi-Fi
- Web Server
- HTML
- JavaScript
- AJAX
- IoT

## Working Principle

1. The ESP32 initializes the connected sensors and LCD.
2. The DHT11 measures temperature and humidity.
3. The soil moisture sensor detects the soil condition.
4. Sensor readings are displayed on the LCD.
5. ESP32 creates a Wi-Fi access point and hosts a web server.
6. The web interface displays the sensor readings.
7. The irrigation pump can be controlled remotely through the web interface using the relay module.
8. This enables convenient monitoring and irrigation management.

## Web Interface

The ESP32 hosts a web-based interface that displays:

- Temperature
- Humidity
- Soil moisture condition
- Relay/Pump status

The interface also provides controls for turning the irrigation pump ON and OFF.

## Project Structure

```text
Smart-Irrigation-System-ESP32/
│
├── README.md
├── Smart_Irrigation_System.ino
├── Smart_Irrigation_System_Report.zip
└── Picture2.png
Source Code

The ESP32 source code is available in:

Smart_Irrigation_System.ino

Project Documentation

The complete academic project report is available in:

Smart_Irrigation_System_Report.zip

Future Enhancements
Automatic irrigation based on soil moisture threshold
Blynk IoT/cloud integration
Mobile application support
Weather-based irrigation
Cloud data logging
Notification alerts
Sensor data analytics
Applications
Smart agriculture
Greenhouse monitoring
Automated irrigation
Home gardening
Water conservation

**Author**
Balabharathi Lokarapu
B.Tech – Electronics and Communication Engineering
Pragati Engineering College
2022–2026

