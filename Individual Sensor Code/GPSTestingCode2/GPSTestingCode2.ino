#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Define the serial connections for GPS and ESP32
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a SoftwareSerial object for GPS communication
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

void setup() {
  Serial.begin(115200); // Start the serial communication
  gpsSerial.begin(9600); // Start the GPS serial communication

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
}

void loop() {
  // Keep reading the GPS data in the main loop
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      displayInfo();
    }
  }
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
