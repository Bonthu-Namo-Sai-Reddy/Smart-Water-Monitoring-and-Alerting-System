# 💧📈 Smart Water Monitoring and Alerting System

📌 Overview  
This project monitors the water quality using a TDS sensor. It reads TDS values and transmits the data from an Arduino to an ESP32 Dev Kit via UART. If the TDS value exceeds the threshold value, an alert SMS is sent continuously to a registered mobile number until clean water is supplied.

🛠️ How It Works  
The TDS Sensor measures the TDS value of the water.  
The Arduino reads the TDS value and transmits data to the ESP32 Dev Kit using UART protocol.  
The ESP32 checks if the TDS value exceeds 250 ppm:  
✅ If TDS ≤ 250: No action is taken.  
❌ If TDS > 250: The system sends continuous SMS alerts to a registered mobile number until the water quality improves.  
The process continues in real-time, ensuring safe water quality monitoring.  

🚀 Features  
✔️ Real-time water quality monitoring  
✔️ Continuous alert system for unsafe water  
✔️ ESP32-based wireless communication  
✔️ Low-cost and efficient solution

🔧 Components Used  
TDS Sensor (for measuring water purity)  
Arduino (for reading sensor data)  
ESP32 Dev Kit (for data processing & communication)  
TWILIO Free Trail Account (for sending alerting messages to target mobile number)  
Power Supply (for running the system)

🛠️ Installation & Setup
1) Clone the Repository : git clone https://github.com/Bonthu-Namo-Sai-Reddy/Smart-Water-Monitoring-and-Alerting-System.git
cd Smart-Water-Quality-Monitoring-and-Alerting-System

3) Upload Code to Arduino & ESP32
Open arduino_code.ino in the Arduino IDE and upload it to Arduino.
Open esp32_code.ino in the Arduino IDE and upload it to ESP32.

4) Connect Hardware & Power On

5) Monitor Water Quality & Get Alerts 🚨

Reference  
https://www.electroniclinic.com/tds-sensor-and-esp32-iot-based-water-quality-monitoring-system/

📜 License  
This project is licensed under the GNU General Public License v3.0.
