#define BLYNK_TEMPLATE_ID "TMPL35bACVfZx"
#define BLYNK_TEMPLATE_NAME "Terrrestial Mapping"

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <BlynkSimpleEsp32.h>


const char* ssid = "arjunkumar";
const char* password = "11916159";

float latitude , longitude;
String  lat_str , lng_str;

const char* thingSpeakApiKey = "PORNZDX2Q0SNDGG9";
const unsigned long thingSpeakChannel = 2332155;

const char* blynkAuthToken = "CLNypzeJXfCtYaBLzRG6o3LudIQElZpU";

// Initialize MPU6050
Adafruit_MPU6050 mpu;

// Define your GPS module's serial connection
#define GPS_SERIAL Serial2

// Initialize TinyGPS++ object
TinyGPSPlus gps;
WiFiClient client;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  // Initialize Blynk
  Blynk.begin(blynkAuthToken, ssid, password);

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("MPU6050 initialization failed!");
    while (1);
  }

  // Initialize GPS module
  GPS_SERIAL.begin(9600);  // Adjust the baud rate to match your GPS module
}

void loop() {
  // Read GPS data
  while (GPS_SERIAL.available() > 0) {
    if (gps.encode(GPS_SERIAL.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        lat_str = String(latitude, 6);
        longitude = gps.location.lng();
        lng_str = String(longitude, 6);
        sendToThingSpeakGPS(lat_str, lng_str);
        sendToBlynkGPS(lat_str, lng_str);
      }
    }
  }

  // Read MPU6050 data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float xAcceleration = a.acceleration.x;
  float yAcceleration = a.acceleration.y;
  float zAcceleration = a.acceleration.z;
  float xRotationDegrees = (g.gyro.x) * 57.29;
  float yRotationDegrees = (g.gyro.y) * 57.29;
  float zRotationDegrees = (g.gyro.z) * 57.29;
  float temperature = temp.temperature;

  sendToBlynk(xRotationDegrees, yRotationDegrees, zRotationDegrees, xAcceleration, yAcceleration, zAcceleration, temperature);
  sendToThingSpeak(xRotationDegrees, yRotationDegrees, zRotationDegrees, xAcceleration, yAcceleration, zAcceleration);

  delay(250); // Send data at regular intervals
}

void sendToThingSpeak(float xRotationDegrees, float yRotationDegrees, float zRotationDegrees, float xAcceleration, float yAcceleration, float zAcceleration) {
  ThingSpeak.setField(1, xAcceleration);
  ThingSpeak.setField(2, yAcceleration);
  ThingSpeak.setField(3, zAcceleration);
  ThingSpeak.setField(4, xRotationDegrees);
  ThingSpeak.setField(5, yRotationDegrees);
  ThingSpeak.setField(6, zRotationDegrees);

  int thingSpeakSuccess = ThingSpeak.writeFields(thingSpeakChannel, thingSpeakApiKey);
  if (thingSpeakSuccess) {
    Serial.println("Data sent to ThingSpeak");
  } else {
    Serial.println("Error sending data to ThingSpeak");
  }
}

void sendToThingSpeakGPS(String latitude, String longitude) {
  ThingSpeak.setField(7, latitude);
  ThingSpeak.setField(8, longitude);
  int thingSpeakSuccess = ThingSpeak.writeFields(thingSpeakChannel, thingSpeakApiKey);
  if (thingSpeakSuccess) {
    Serial.println("GPS data sent to ThingSpeak");
  } else {
    Serial.println("Error sending GPS data to ThingSpeak");
  }
}

void sendToBlynk(float xRotationDegrees, float yRotationDegrees, float zRotationDegrees, float xAcceleration, float yAcceleration, float zAcceleration, float temperature) {
  Blynk.virtualWrite(0, xAcceleration);
  Blynk.virtualWrite(1, yAcceleration);
  Blynk.virtualWrite(2, zAcceleration);
  Blynk.virtualWrite(3, xRotationDegrees);
  Blynk.virtualWrite(4, yRotationDegrees);
  Blynk.virtualWrite(5, zRotationDegrees);
  Blynk.virtualWrite(6, temperature);
  Serial.println("Reading has been sent to Blynk");
}

void sendToBlynkGPS(String latitude, String longitude) {
  Blynk.virtualWrite(7, latitude);
  Blynk.virtualWrite(8, longitude);
  Serial.println("GPS data sent to Blynk");
}
