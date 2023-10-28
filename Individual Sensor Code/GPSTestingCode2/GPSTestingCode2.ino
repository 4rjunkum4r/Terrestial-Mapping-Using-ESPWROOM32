#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
SoftwareSerial ss(0,1);

void setup() {
  Serial.begin(115200);
  Serial.println("********** Starting Program To Located GPS Coordinate **********");

  ss.begin(9600);

}

void loop() {
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
}

void displayInfo() {

  if (gps.location.isValid()) {
    Serial.println("Latitude:- ");
    Serial.println(gps.location.lat());
    delay(1000);
    Serial.println("Longitude:- ");
    Serial.println(gps.location.lng());
    delay(1000);
  } else {
    Serial.println(F("INVALID"));
  }

} 
