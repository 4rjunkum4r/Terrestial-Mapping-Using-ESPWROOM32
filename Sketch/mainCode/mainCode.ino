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

static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;
float latitude , longitude;
String  lat_str , lng_str;

Adafruit_MPU6050 mpu;

TinyGPSPlus gps;

SoftwareSerial gpsSerial(RXPin, TXPin);

WiFiClient client;

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  gpsSerial.begin(9600);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  ThingSpeak.begin(client);

  Blynk.begin("CLNypzeJXfCtYaBLzRG6o3LudIQElZpU", ssid, pass, "blynk.cloud", 80);

}

void loop() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
        Serial.print("Latitude = ");
        Serial.println(lat_str);
        Serial.print("Longitude = ");
        Serial.println(lng_str);
      } delay(1000);
    }
  }


  float xRotationDegrees = (g.gyro.x) * 57.29;
  float yRotationDegrees = (g.gyro.y) * 57.29;
  float zRotationDegrees = (g.gyro.z) * 57.29;


  ThingSpeak.setField(1, a.acceleration.x);
  ThingSpeak.setField(2, a.acceleration.x);
  ThingSpeak.setField(3, a.acceleration.x);
  ThingSpeak.setField(4, xRotationDegrees);
  ThingSpeak.setField(5, yRotationDegrees);
  ThingSpeak.setField(6, zRotationDegrees);
  ThingSpeak.setField(7, lat_str);
  ThingSpeak.setField(8, lng_str);

  Blynk.virtualWrite(0, a.acceleration.x);
  Blynk.virtualWrite(1, a.acceleration.y);
  Blynk.virtualWrite(2, a.acceleration.z);
  Blynk.virtualWrite(3, xRotationDegrees);
  Blynk.virtualWrite(4, yRotationDegrees);
  Blynk.virtualWrite(5, zRotationDegrees);
  Blynk.virtualWrite(6, temp.temperature);
  Blynk.virtualWrite(7, gps.location.lat());
  Blynk.virtualWrite(8, gps.location.lng());

  ThingSpeak.writeFields(myChannelNumber, myApiKey);
  Blynk.run();

}
