#include <ESP32Servo.h>

static const int MIN = 500;       
static const int MAX = 2400;
static const int SERVO_FREQ = 50; 

enum Opperation {OPEN, CLOSE, CLOSE45, OPEN90};

class Quadrant {
  public: 
    Quadrant(int pin1, int pin2);
    void moveTo(Opperation angle); 
    void slowMoveTo(Opperation angle); 
    void setManual(); 
  private: 
    int servoPin1;  //For closing 
    int servoPin2;  //For opening
    Servo servo1;
    Servo servo2;
};