#define BLYNK_TEMPLATE_ID "TMPL35bACVfZx"
#define BLYNK_TEMPLATE_NAME "Terrrestial Mapping"
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

#include <WiFi.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <ThingSpeak.h>
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "arjunkumar";
char pass[] = "11916159";

const int myChannelNumber = 2332155 ;
const char* myApiKey = "PORNZDX2Q0SNDGG9";
const char* server = "api.thingspeak.com";


Adafruit_MPU6050 mpu;

TinyGPSPlus gps;

SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

WiFiClient client;

void setup() {

  Serial.begin(115200);

  gpsSerial.begin(9600);

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

  ThingSpeak.begin(client);

  Blynk.begin("CLNypzeJXfCtYaBLzRG6o3LudIQElZpU", ssid, pass, "blynk.cloud", 80);

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

  ThingSpeak.setField(1, a.acceleration.x);
  ThingSpeak.setField(2, a.acceleration.x);
  ThingSpeak.setField(3, a.acceleration.x);
  ThingSpeak.setField(4, xRotationDegrees);
  ThingSpeak.setField(5, yRotationDegrees);
  ThingSpeak.setField(6, zRotationDegrees);


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
    Blynk.virtualWrite(7, gps.location.lat());
    Blynk.virtualWrite(8, gps.location.lng());
    Blynk.run();
  } else {
    Serial.println("GPS signal not valid");
  }
  Serial.println();
}
