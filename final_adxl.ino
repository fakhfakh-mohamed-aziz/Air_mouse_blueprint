#include <BleMouse.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define LEFTBUTTON 19
#define RIGHTBUTTON 18

#define DEADZONE 0.2
#define SENSITIVITY 6.0

BleMouse bleMouse;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

float smoothX = 0;
float smoothY = 0;
const float alpha = 0.8;

unsigned long lastClick = 0;
const unsigned long debounceDelay = 200;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(LEFTBUTTON, INPUT_PULLUP);
  pinMode(RIGHTBUTTON, INPUT_PULLUP);

  bleMouse.begin();

  if (!accel.begin()) {
    while (1);
  }

  accel.setRange(ADXL345_RANGE_4_G);
}

void loop() {
  if (!bleMouse.isConnected()) return;

  sensors_event_t event;
  accel.getEvent(&event);

  float x = event.acceleration.y;
  float y = -event.acceleration.x;

  if (abs(x) < DEADZONE) x = 0;
  if (abs(y) < DEADZONE) y = 0;

  smoothX = alpha * smoothX + (1 - alpha) * x;
  smoothY = alpha * smoothY + (1 - alpha) * y;

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

  delay(15);
}
