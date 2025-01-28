# Arduino Projects Repository  

Welcome to the **Arduino Projects Repository**! This collection showcases personal projects using **Arduino, ESP32, and custom PCBs**. Each project includes source code, circuit diagrams, and detailed documentation.  

---

## Available Projects  

### 1. **EXP13: Smart Irrigation System with ESP32 and MQTT**  
**Description:**  
Control a water pump and monitor soil moisture using an **ESP32** with MQTT for real-time data transmission.  

**Components:**  
- ESP32 DevKit  
- Soil Moisture Sensor (Analog)  
- 5V Submersible Pump  
- MQTT Broker (e.g., Mosquitto)  

**Files:**  
- `EXP13.ino`: Main code.  
- [Circuit Diagram](./images/EXP13.png)  
- [Setup Photo](./images/EXP13_S.jpg)  

---

### 2. **EXP15: LoRa-Based Wireless Communication**  
**Description:**  
Long-range communication between two devices using **LoRa modules** (433 MHz).  

**Components:**  
- Arduino Nano  
- LoRa RA-02 Module  
- 16x2 LCD (Receiver Side)  

**Files:**  
- `EXP15_Transmitter.ino`: Transmitter code.  
- `EXP15_Receiver.ino`: Receiver code.  
- [Circuit Diagram](./images/EXP15.png)  

---

### 3. **EXP2: Fan Speed Control with Temperature & Joystick**  
**Description:**  
Adjust fan speed automatically (via DS18B20 sensor) or manually (via joystick).  

**Components:**  
- Arduino Nano  
- DS18B20 Temperature Sensor  
- Joystick Module  
- DC Motor + MOSFET  

**Files:**  
- `EXP2.ino`: Main code.  
- [Circuit Diagram](./images/EXP2.jpg)  
- [Setup Photo](./images/EXP2_S.jpg)  

---

### 4. **EXP5: RFID-Based Access Control with Audio Feedback**  
**Description:**  
Secure access system using **MFRC522 RFID** and audio alerts via DFPlayer Mini.  

**Components:**  
- Arduino Nano  
- MFRC522 RFID Reader  
- DFPlayer Mini (MP3)  
- Solenoid Lock  

**Files:**  
- `EXP5.ino`: Main code.  
- [Circuit Diagram](./images/EXP5.png)  
- [Setup Photo](./images/EXP5_S.jpg)  

---

### 5. **EXP7: Ultrasonic Water Level Monitoring**  
**Description:**  
Measure water levels in real-time using an **HC-SR04 Ultrasonic Sensor**.  

**Components:**  
- Arduino Uno  
- HC-SR04 Sensor  
- 16x2 LCD  
- Buzzer (for alerts)  

**Files:**  
- `EXP7.ino`: Main code.  
- [Circuit Diagram](./images/EXP7.jpg)  
- [Setup Photo](./images/EXP7.png)  

---

## How to Use  
1. **Clone the Repository**:  
   ```bash  
   git clone https://github.com/your-username/Arduino-Projects-Collection.git  
