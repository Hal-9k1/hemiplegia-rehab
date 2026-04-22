#pragma once

class Motor
{
public:
  Motor(int stepPin, int dirPin);
  void move(int steps, int stepsPerSec);
  void wait();
  void onIrqWrap();

private:
  int stepPin;
  int dirPin;
  unsigned int stepSlice;
  unsigned int stepChannel;
  int remTicks;
};
