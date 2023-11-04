#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ThingSpeak.h>
#include <WiFi.h>

static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;
float latitude , longitude;
String  lat_str , lng_str;

// repace your wifi username and password
const char* ssid     = "arjunkumar";
const char* password = "11916159";
unsigned long myChannelNumber = 2332155;
const char * myWriteAPIKey = "PORNZDX2Q0SNDGG9";

// The TinyGPS++ object
TinyGPSPlus gps;
WiFiClient  client;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  ThingSpeak.begin(client);
}
void loop()
{
  while (ss.available() > 0){
    if (gps.encode(ss.read()))
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
        ThingSpeak.setField(7, lat_str);
        ThingSpeak.setField(8, lng_str);
        ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); 
      }
     delay(1000);
     Serial.println();  
    }
  }
}
