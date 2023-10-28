#include <Wire.h>
#include <TinyGPSPlus.h>

#define RXD2 16
#define TXD2 17
HardwareSerial neogps(1);
char dataCmd = 0;

#define NMEA 0

TinyGPSPlus gps;

void setup()
{
  Serial.begin(115200);
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  if (NMEA)
  {
    while (neogps.available())
      dataCmd = (char)neogps.read();
    Serial.print(dataCmd);
  }
else {
  boolean newData = false;
  for (unsigned long start = millis();
       millis() - start < 1000;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }
if (newData == true) {
  newData = false;
  Serial.print(gps.satellites.value());
}
}}
