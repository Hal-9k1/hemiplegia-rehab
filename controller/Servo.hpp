#pragma once

class Servo
{
public:
  Servo(int pin, float servoOverOutRatio);
  void move(float angle);
 
private:
  int pin;
  float gearRatio;
};
