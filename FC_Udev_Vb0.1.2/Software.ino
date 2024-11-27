//                         C|A|T                         //
//              COSMIC AEROSPACE TECHNOLOGY              //
//                FC-Udev Flight Software                //
//                   November 26th 2024                  //     
//                        CANADA                         //
//=======================================================//
//      Consider Donating <3: cosmicaero.space/donate    //

/*
Version b0.1.2

- Optimized Code 
- SD-card compatible
- Toggled Data logging
- More readable
- Use of SdFat library

NOTE: If you are using an SD card module, you must insert the 
Micro SD card into the slot. Don't forget to format the card (FAT32)!
*/

// Libraries
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// Constants and Variables
const int LaunchDetectLED = 5, pyro1 = 7, pyro2 = 8, buzzer = 3, cnt1 = 2, cnt2 = 4;
const int MPU_ADDR = 0x68, chipSelect = 10;
const float PressureAtSea = 1003.80, alpha = 0.85, alpha2 = 0.5;
unsigned long previousTime = 0;
float maxAltitude = 0, initialAltitude = 0;
int state = 0;

// Apogee delay in milliseconds (adjust as needed)
const int delayTime = 1000;

// True if you have an SD card module | False otherwise (Default)
bool dataLogging = false;

Adafruit_MPU6050 mpu;
Adafruit_BMP280 bmp;

SdFat SD;
SdFile myFile;

void setup() {
    Wire.begin();
    Serial.begin(115200);

    // Initialize sensors
    while (!mpu.begin() || !bmp.begin(0x76)) {
        Serial.println("Initialization Failed! Check connections.");
        delay(1000);
    }
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, Adafruit_BMP280::SAMPLING_X1,
                    Adafruit_BMP280::SAMPLING_X1, Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_1);

    // Initialize pins
    pinMode(LaunchDetectLED, OUTPUT);
    pinMode(pyro1, OUTPUT);
    pinMode(pyro2, OUTPUT);
    pinMode(cnt1, OUTPUT);
    pinMode(cnt2, OUTPUT);
    pinMode(buzzer, OUTPUT);

    initialAltitude = bmp.readAltitude(PressureAtSea);

    if (dataLogging) {
        if (!SD.begin(chipSelect, SD_SCK_MHZ(16))) {  // Initialize with high-speed SPI
            Serial.println("SD card initialization failed!");
            while (1);
        }
        if (!myFile.open("data.txt", O_RDWR | O_CREAT | O_AT_END)) {  // Open file for append
            Serial.println("Error opening data.txt.");
            while (1);
        } else {
            myFile.println("testing 1, 2, 3");  // Write initial test log
            myFile.sync();
            Serial.println("SD card initialized, ready to write.");
        }
    }

    Serial.println("FC-Udev is Ready for Flight");
    startup();
}

void loop() {
    int read2 = analogRead(A0);
    int read1 = analogRead(A1);
    if (read1 >= 200) {
        digitalWrite(cnt1, HIGH);
    } else {
        digitalWrite(cnt1, LOW);
    }
    if (read2 >= 200) {
        digitalWrite(cnt2, HIGH);
    } else {
        digitalWrite(cnt2, LOW);
    }

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    printTelemetry();

    // Launch detection
    if (state == 0 && abs(a.acceleration.y) > 45) {  // Sensitivity adjustment
        digitalWrite(LaunchDetectLED, HIGH);
        state = 1;
    }
    if (state == 1) flight();
}

// Flight Function
void flight() {
    float temp = bmp.readTemperature() - 3.8; //  Temperature w/ Estimated Error value
    float pressure = bmp.readPressure() / 1000.0; // Convert to kPa
    float CurrentAltitude = bmp.readAltitude(PressureAtSea) - initialAltitude;

    // Saves Highest Altitude in maxAltitude
    if (CurrentAltitude > maxAltitude) {
        maxAltitude = CurrentAltitude;
    }
    
    // Trigger deployment at apogee
    if ((maxAltitude > CurrentAltitude + 1.00) && state == 1) { 
        deploy();  // Deployment only called once
    }

    printTelemetry();  // Log telemetry during flight
}


// Deploy Recovery System
void deploy() {
    // Update the state to indicate deployment has occurred
    state = 2;  // New state to indicate post-deployment
    
    // Apogee delay (adjustable)
    delay(delayTime);  // Blocking delay to wait for deployment

    // Activate recovery system
    digitalWrite(pyro1, HIGH);
    digitalWrite(pyro2, HIGH);
    tone(buzzer, 2000, 500);  // Short buzzer tone for deployment

    delay(1500);  // Duration of charge burn
    digitalWrite(pyro1, LOW);
    digitalWrite(pyro2, LOW);

    // Start logging telemetry continuously
    Serial.println("Entering post-deployment telemetry logging...");
    while (true) {
        printTelemetry();  // Log telemetry in an infinite loop
        delay(100);  // Prevent flooding telemetry output
    }
}


void printTelemetry() {
    float temp = bmp.readTemperature();
    float pressure = bmp.readPressure() / 1000.0;  // Convert to kPa
    float CurrentAltitude = bmp.readAltitude(PressureAtSea) - initialAltitude;

    Serial.print("Temp: "); Serial.print(temp); Serial.print(" C, ");
    Serial.print("Pressure: "); Serial.print(pressure); Serial.print(" kPa, ");
    Serial.print("Altitude: "); Serial.print(CurrentAltitude); Serial.println(" m");
if (dataLogging) {
    if (myFile.isOpen()) {
        myFile.print(millis());
        myFile.print(",");
        myFile.print(temp);
        myFile.print(",");
        myFile.print(pressure);
        myFile.print(",");
        myFile.println(CurrentAltitude);
        myFile.sync();  // Ensure data is written to the SD card
    } else {
        Serial.println("Error writing to SD card.");
    }
}
    delay(50);  // Prevent spamming
}

// Startup Sequence
void startup() {
    for (int i = 0; i < 3; i++) {
        tone(buzzer, 1800, 100);
        delay(200);
        noTone(buzzer);
    }
}
