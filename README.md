AIR MOUSE
---
My first hardware project is an air mouse, a tilt-based controller that lets you move a cursor on your phone, pc or smart TV!

---
Usage of the air mouse
---
Have you ever dreamed about sitting on your couch in front of a tv and swapping channels with your hand like a king? Well search no more! Here, you'll find the code to realize that dream! With this controller, you can control computers, smart TVs and (surprizingly) even phones and tablets!
![20260118_113648](https://github.com/user-attachments/assets/c723e660-463c-47b3-96b6-4994af5adf5c) 

---
Components
---
 -An ESP32 card
 -An ADXL345 gyro (or an MPU6050, both codes are available)
 -Some wires
 -A breadboard (not mandatory)
 -Two buttons
 and that's it!

 ---
 Software requirements
 ---
 In the arduino IDE you'll need the following libraries:
  -<BleMouse.h>
  -<Wire.h>
  -<Adafruit_Sensor.h>
  -<Adafruit_ADXL345_U.h>

---
Code Files
---
In the "Code" repository, you'll find 3 files:
 -The "Debugging" file: This code lets you know if your gyro is working, by showing the values in the IDE
 -The "final_adxl": Really it's the only file you'll need. It's containing the code that makes the air mouse work (using the adxl gyro)
 - The "final_mpu": For those who want to use the mpu gyro, the code is also available

---
