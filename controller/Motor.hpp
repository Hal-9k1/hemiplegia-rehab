#pragma once

class Motor
{
public:
  Motor(int stepPin, int dirPin);
  void move(unsigned int steps, unsigned int stepsPerSec);
  void setDirection(bool forward);
  void wait();
  void onMotionDone();

private:
  int stepPin;
  int dirPin;
  unsigned int stepPioMachine;
  bool motionInProgress;
};
