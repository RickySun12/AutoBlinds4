#include <Quadrant.h>

Quadrant::Quadrant(int pin1, int pin2) {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  servoPin1 = pin1; 
  servoPin2 = pin1;
  servo1.setPeriodHertz(SERVO_FREQ);
  servo1.attach(pin1, MIN, MAX);
  servo2.setPeriodHertz(SERVO_FREQ);
  servo2.attach(pin2, MIN, MAX);
}

void Quadrant::moveTo(Opperation angle) {
  if (angle == OPEN) {
    servo1.write(0);
    for (int pos = 180; pos >= 10; pos--) {
      servo2.write(pos);
      vTaskDelay(15); 
    }
  }
  else if (angle == CLOSE) {
    servo2.write(180);
    for (int pos = 10; pos <= 180; pos++) {
      servo1.write(pos);
      vTaskDelay(15); 
    }
  }
  else if (angle == CLOSE45) {
    servo2.write(180);
    for (int pos = 10; pos <= 120; pos++) {
      servo1.write(pos);
      vTaskDelay(15); 
    }
  }
  else {
    servo1.write(0);
    for (int pos = 180; pos >= 72; pos--) {
      servo2.write(pos);
      vTaskDelay(15); 
    }
  }
}

void Quadrant::slowMoveTo(Opperation angle) {
  if (angle == OPEN) {
    //servo1.write(0);
    for (int pos = 180; pos >= 0; pos--) {
      servo1.write(pos);
      vTaskDelay(1000); 
    }
    for (int pos = 180; pos >= 10; pos--) {
      servo2.write(pos);
      vTaskDelay(2000); 
    }
  }
  else {
    //servo2.write(180);
    for (int pos = 10; pos <= 180; pos++) {
      servo2.write(pos);
      vTaskDelay(1000); 
    }
    for (int pos = 10; pos <= 180; pos++) {
      servo1.write(pos);
      vTaskDelay(2000); 
    }
  }
}

void Quadrant::setManual() {
  servo1.write(0);
  servo2.write(180);
}