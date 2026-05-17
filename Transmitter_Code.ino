#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

MPU6050 mpu;
SoftwareSerial BT(2, 3); // RX, TX for Bluetooth

int16_t ax, ay, az;
char command;

void setup() {
  Wire.begin();
  Serial.begin(9600);     // Debugging via USB
  BT.begin(9600);         // HC-05 Bluetooth

  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1); // Stop if sensor not found
  }

  delay(1000); // Let sensor stabilize
}

void loop() {
  // Read acceleration values
  mpu.getAcceleration(&ax, &ay, &az);

  // Debugging output
  Serial.print("X: "); Serial.print(ax);
  Serial.print(" | Y: "); Serial.print(ay);
  Serial.print(" | Z: "); Serial.println(az);

  // Gesture detection
  if (ay > 9000) {
    command = 'F'; // Tilt forward
  } 
  else if (ay < -9000) {
    command = 'B'; // Tilt backward
  } 
  else if (ax > 10000) {
    command = 'R'; // Tilt right  ✅ fixed
  } 
  else if (ax < -10000) {
    command = 'L'; // Tilt left   ✅ fixed
  } 
  else {
    command = 'S'; // Stop
  }

  // Send command to car
  BT.write(command);
  Serial.println(command);

  delay(200); // Prevent flooding
}
