#include <HardwareSerial.h>

HardwareSerial GPS(2);  // UART2 on ESP32

void setup() {
  Serial.begin(9600);
  GPS.begin(9600);
}

void loop() {
  if (GPS.available()) {
    char c = GPS.read();
    Serial.print(c);
  }
}
