#define BLYNK_TEMPLATE_ID "TMPL35bACVfZx"
#define BLYNK_TEMPLATE_NAME "Terrrestial Mapping"

#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <BlynkSimpleEsp32.h>

//Wifi Section for our project
char ssid[] = "arjunkumar";
char pass[] = "11916159";

//Making obect of MPU library
Adafruit_MPU6050 mpu;

void setup() {

  Serial.begin(115200);
  Blynk.begin("CLNypzeJXfCtYaBLzRG6o3LudIQElZpU", ssid, pass, "blynk.cloud", 80);

  //MPU6050 Section
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
  //Blynk Section


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
  float xRotationDegrees = (g.gyro.x)*57.29;
  float yRotationDegrees = (g.gyro.y)*57.29;
  float zRotationDegrees = (g.gyro.z)*57.29;
  //  // Send the sensor data to Blynk
  Blynk.virtualWrite(0, a.acceleration.x);
  Blynk.virtualWrite(1, a.acceleration.y);
  Blynk.virtualWrite(2, a.acceleration.z);

  Blynk.virtualWrite(3, xRotationDegrees);
  Blynk.virtualWrite(4, yRotationDegrees);
  Blynk.virtualWrite(5, zRotationDegrees);

  Blynk.virtualWrite(6, temp.temperature);
  //
  //  // Process all Blynk requests
  Blynk.run();

}
