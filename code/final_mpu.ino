#include <BleMouse.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define LEFTBUTTON 19
#define RIGHTBUTTON 18

#define DEADZONE 0.05
#define SENSITIVITY 8.0

Adafruit_MPU6050 mpu;
BleMouse bleMouse;

float smoothX = 0;
float smoothY = 0;
const float alpha = 0.8;  

unsigned long lastClick = 0;
const unsigned long debounceDelay = 200;

void setup() {
  Serial.begin(115200);

  pinMode(LEFTBUTTON, INPUT_PULLUP);
  pinMode(RIGHTBUTTON, INPUT_PULLUP);

  bleMouse.begin();

  if (!mpu.begin()) {
    while (1);
  }

  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  if (!bleMouse.isConnected()) return;

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float x = -g.gyro.z;
  float y = -g.gyro.x;

  if (abs(x) < DEADZONE) x = 0;
  if (abs(y) < DEADZONE) y = 0;

  smoothX = alpha * smoothX + (1 - alpha) * x;
  smoothY = alpha * smoothY + (1 - alpha) * y;
  Serial.println("Loop running");
  delay(500);

//  Serial.print("X: "); Serial.print(smoothX);
//  Serial.print(" | Y: "); Serial.println(smoothY);

  bleMouse.move(smoothX * SENSITIVITY, smoothY * SENSITIVITY);

  unsigned long now = millis();

  if (!digitalRead(LEFTBUTTON) && now - lastClick > debounceDelay) {
    bleMouse.click(MOUSE_LEFT);
    lastClick = now;
  }

  if (!digitalRead(RIGHTBUTTON) && now - lastClick > debounceDelay) {
    bleMouse.click(MOUSE_RIGHT);
    lastClick = now;
  }
}
