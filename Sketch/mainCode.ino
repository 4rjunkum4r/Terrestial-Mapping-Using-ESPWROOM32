#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

//Wifi Section for our project
const char* ssid = "espProject";
const char* password = "11916159";

//Making obect of MPU library
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  //-------------------------------------------------------------------------------------------------------------------
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to the Wi-Fi network");
  Serial.println("SSID: ");
  Serial.print(ssid);
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());
  //----------------------------------------------------------------------------------------------------------------

  Serial.println("\nMPU6050 test!");
  while (!mpu.begin()) {
    delay(1000);
    Serial.println("Failed to find MPU6050 chip");
  }
  
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(100);

}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("+---------------+\n");
  Serial.print("|Acceleration   |\n");
  Serial.print("+---------------+\n");
  Serial.print("X: ");
  Serial.print(a.acceleration.x);
  Serial.print(" m/s^2");
  Serial.print("\nY: ");
  Serial.print(a.acceleration.y);
  Serial.print(" m/s^2");
  Serial.print("\nZ: ");
  Serial.print(a.acceleration.z);
  Serial.print(" m/s^2");
  Serial.print("\n+---------------+\n");

  Serial.print("\n+---------------+\n");
  Serial.print("|Rotation       |\n");
  Serial.print("+---------------+\n");
  Serial.print("X: ");
  Serial.print(g.gyro.x);
  Serial.print(" rad/s");
  Serial.print("\nY: ");
  Serial.print(g.gyro.y);
  Serial.print(" rad/s");
  Serial.print("\nZ: ");
  Serial.print(g.gyro.z);
  Serial.print(" rad/s");
  Serial.print("\n+---------------+\n");

  Serial.print("\n+---------------+\n");
  Serial.print("|Temperature    |\n");
  Serial.print("+---------------+\n");
  Serial.print(temp.temperature);
  Serial.println(" °C ");
  Serial.print("+---------------+\n");

  Serial.println("");
  delay(500);

}
