// Test if all 4 servos are functional
#include <Servo.h>

//Servos
//ensure you have wired the servos to these ports on the nano
#define servo1_pin 2
#define servo2_pin 3
#define servo3_pin 4
#define servo4_pin 5

// Create servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  // Attach servos to their respective pins
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo3.attach(servo3_pin);
  servo4.attach(servo4_pin);
}

void loop() {
  // Move servos to 0 degrees
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  delay(1000); // Wait for 1 second

  // Move servos to 180 degrees
  servo1.write(180);
  servo2.write(180);
  servo3.write(180);
  servo4.write(180);
  delay(1000); // Wait for 1 second
}
