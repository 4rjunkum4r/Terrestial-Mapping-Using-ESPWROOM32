#define BLYNK_TEMPLATE_ID "TMPL35bACVfZx"
#define BLYNK_TEMPLATE_NAME "Terrrestial Mapping"
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "arjunkumar";
char pass[] = "11916159";

Adafruit_MPU6050 mpu;
TinyGPSPlus gps;

SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

void setup() {

  Serial.begin(115200);
  gpsSerial.begin(9600);
  Blynk.begin("CLNypzeJXfCtYaBLzRG6o3LudIQElZpU", ssid, pass, "blynk.cloud", 80);
  Serial.println("GPS Module Test");

  // Some modules require a warm-up period and a few initial readings
  // Read data from GPS for a few seconds to initialize
  unsigned long start = millis();
  while (millis() - start < 5000) {
    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        displayInfo();
      }
    }
  }



  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);


}

void loop() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float xRotationDegrees = (g.gyro.x) * 57.29;
  float yRotationDegrees = (g.gyro.y) * 57.29;
  float zRotationDegrees = (g.gyro.z) * 57.29;

  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      displayInfo();
    }
  }


  Blynk.virtualWrite(0, a.acceleration.x);
  Blynk.virtualWrite(1, a.acceleration.y);
  Blynk.virtualWrite(2, a.acceleration.z);
  Blynk.virtualWrite(3, xRotationDegrees);
  Blynk.virtualWrite(4, yRotationDegrees);
  Blynk.virtualWrite(5, zRotationDegrees);
  Blynk.virtualWrite(6, temp.temperature);
  Blynk.run();

}
void displayInfo() {
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat());
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng());
  } else {
    Serial.println("GPS signal not valid");
  }
  Serial.println();
}
