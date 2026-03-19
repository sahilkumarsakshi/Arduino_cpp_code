# 🕶️ Ultrasonic Smart Glasses for the Blind

![Project Status](https://img.shields.io/badge/Status-Prototype-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Hardware](https://img.shields.io/badge/Hardware-Arduino_Nano-00979D)

An open-source, wearable assistive technology device designed to provide hands-free navigation and upper-body obstacle detection for the visually impaired using stereoscopic ultrasonic sensors and proportional haptic feedback.

---

## 📖 Overview
Traditional white canes are excellent for detecting ground-level obstacles but leave the user vulnerable to head-level hazards (like low branches or hanging signs). This project solves that by integrating **Time-of-Flight (ToF)** distance calculation into a lightweight pair of glasses. 

Instead of an alarming auditory beep, this system uses **non-blocking PWM haptic feedback**. The closer the user gets to an obstacle, the stronger the vibration motor pulses, providing an intuitive "spatial feel" of their surroundings.

## ✨ Key Features
* **Stereoscopic Detection:** Dual HC-SR04 sensors provide a wide field of view (Left and Right).
* **Proportional Haptic Feedback:** Vibration intensity scales dynamically with proximity.
* **Non-Blocking Code Architecture:** Software timeouts prevent the microcontroller from freezing if a sensor misses an echo.
* **Hardware Protection:** Includes a transistor-based motor driver with a flyback diode to protect the microcontroller from inductive voltage spikes.

---

## 🛠️ Bill of Materials (Hardware)
| Component | Quantity | Description |
| :--- | :--- | :--- |
| **Arduino Nano** | 1 | The main 8-bit microcontroller (ATmega328P). |
| **HC-SR04** | 2 | Ultrasonic distance sensors. |
| **10mm Coin Motor** | 1 | Pancake vibration motor for haptic feedback. |
| **BC547 NPN** | 1 | Transistor to safely drive the motor. |
| **1N4007 Diode** | 1 | Flyback protection diode. |
| **1kΩ Resistor** | 1 | Current limiting resistor for the transistor base. |
| **9V Battery** | 1 | Power source. |
| **LM7805** | 1 | 5V Voltage Regulator (Optional, if not using Arduino VIN). |

---

## ⚙️ Circuit Diagram

![Schematic diagram](Schematic%20diagram.png)

**Pin Mapping:**
* `D2` -> Left Sensor TRIG
* `D3` -> Left Sensor ECHO
* `D4` -> Right Sensor TRIG
* `D5` -> Right Sensor ECHO
* `D10` -> Transistor Base (via 1k Resistor) -> Motor
* `D13` -> Status LED

---

## 🚀 Installation & Setup

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/sahilkumarsakshi/ultrasonic-smart-glasses.git](https://github.com/sahilkumarsakshi/ultrasonic-smart-glasses.git)
Open the code: Open code/ultrasonic_smart_glasses.ino in the Arduino IDE.

Select Board: Go to Tools > Board and select Arduino Nano.

Select Port: Go to Tools > Port and select the active COM port.

Upload: Click the Upload button to flash the code to the microcontroller.

🔮 Future Scope
This V1 prototype is fully functional, but future iterations aim to include:

Migration to a 32-bit ESP32 architecture for faster real-time processing.

Integration of Bluetooth Low Energy (BLE) to communicate with a smartphone app for GPS turn-by-turn navigation.

Use of smaller, strictly 3.3V sensors for a slimmer, more ergonomic 3D-printed frame.

📄 License
This project is licensed under the MIT License - see the LICENSE file for details. You are free to use, modify, and distribute this hardware and software design.

***
