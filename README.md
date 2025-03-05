# 🚀 FC-Udev Flight Software

## 🌟 Overview  
**FC-Udev Flight Software** is an open-source project designed to operate and manage model rockets, perfect for rocketeers eager to explore the integration of electronics into their projects. Developed by **Cosmic Aerospace Technology (C|A|T)**, this software provides a robust, modular foundation for enthusiasts, beginners, and professionals to build, deploy, and log telemetry for flight systems. Optimized for Arduino-based platforms, it integrates sensor modules to monitor real-time telemetry, detect events, and execute autonomous operations.

This repository represents our commitment to fostering innovation, learning, and collaboration within the aerospace and electronics communities.

---

## ✨ Features  
- **Open Source**: Freely available for non-commercial and educational purposes.  
- **Telemetry Logging**: Seamless integration with SD card modules for recording temperature, pressure, altitude, and other sensor data.  
- **Modular Design**: Built for flexibility and ease of customization.  
- **Advanced Sensor Support**: Compatible with the Adafruit MPU6050 and BMP280 modules for precise accelerometer, gyroscope, and barometric readings.  
- **Event Detection**: Includes launch detection and apogee recovery deployment logic.  
- **User Configurable**: Allows toggling features like data logging and apogee delay for different mission profiles.  

---

## 🛠️ Hardware Requirements  
To use this software, ensure the following hardware components are available:  
1. **Flight Computer**: Arduino-compatible board (e.g., Arduino Mega, Uno, or Nano).  
2. **Sensors**:  
   - Adafruit MPU6050 (Accelerometer and Gyroscope)  
   - Adafruit BMP280 (Barometric Pressure and Temperature Sensor)  
3. **SD Card Module**: Compatible with SPI interface.  
4. **Peripherals**:  
   - LEDs  
   - Buzzers  
   - Pyrotechnic outputs (for recovery system deployment)  

---

## 🚀 Getting Started  

### Prerequisites  
- **Arduino IDE**: Install the latest version.  
- **Libraries**:  
  - [Adafruit Sensor Library](https://github.com/adafruit/Adafruit_Sensor)  
  - [Adafruit BMP280 Library](https://github.com/adafruit/Adafruit_BMP280_Library)  
  - [Adafruit MPU6050 Library](https://github.com/adafruit/Adafruit_MPU6050)  
  - [SDFat Library](https://github.com/greiman/SdFat)  

### Installation  
1. Clone this repository or download the `.ino` file.  
2. Open the `.ino` file in the Arduino IDE.  
3. Install the required libraries listed above.  
4. Upload the sketch to your Arduino-compatible board.  

---

## 🧩 Code Structure  

### Key Sections  
- **Setup**: Initializes the sensors, peripherals, and SD card module.  
- **Loop**: Contains the main program logic for telemetry logging, launch detection, and recovery system deployment.  
- **Functions**:  
  - `printTelemetry()`: Logs and prints sensor data.  
  - `flight()`: Handles the flight phase, including event-based logic.  
  - `deploy()`: Executes recovery system deployment.  
  - `startup()`: Provides a startup sequence for user feedback.  

---

## 🛠️ How to Use  

1. **Data Logging**:  
   - Enable or disable logging by setting the `dataLogging` variable in the code.  
2. **Customizing Deployment**:  
   - Adjust the apogee delay using the `delayTime` variable.  
3. **Telemetry**:  
   - View real-time data via the serial monitor or access the recorded telemetry in the `data.txt` file on the SD card.  

---

## 🤝 Contribution  
Contributions are welcome! Whether you want to fix a bug, enhance the software, or suggest a new feature:  
1. Fork the repository.  
2. Create a branch for your feature/bugfix.  
3. Submit a pull request with a detailed explanation.  

---

## 📜 License  
This project is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-nd/4.0/

---

## 🙏 Acknowledgments  
We thank the global open-source community for their contributions to the Arduino ecosystem. Special recognition goes to:  
- Adafruit Industries for their robust sensor libraries.  
- Greiman for the SDFat library.  

---

## 💬 Support  
For questions, feature requests, or bug reports, please create an issue in the [Issues Section](https://github.com/your-username/FC-Udev-Flight-Software/issues).  
If you find this project useful, consider donating to us at [cosmicaero.space/donate](https://cosmicaero.space/donate).  

---

**Cosmic Aerospace Technology (C|A|T)**  
*Unlocking the sky through open innovation.*  
[cosmicaero.space](https://cosmicaero.space)  
