#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int pushUpCount = 0;
bool goingDown = false;
float accelZ;
float thresholdDown = 0.85; 
float thresholdUp = 1.15;   

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully");
  } else {
    Serial.println("MPU6050 connection failed");
    while(1);
  }
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  
  accelZ = az / 16384.0;

  if (accelZ < thresholdDown && !goingDown) {
    goingDown = true;
  }

  if (accelZ > thresholdUp && goingDown) {
    goingDown = false;
    pushUpCount++;
    Serial.print("Push-up count: ");
    Serial.println(pushUpCount);
  }

  delay(100); 
}