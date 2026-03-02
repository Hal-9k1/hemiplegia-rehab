#pragma once

#include "hardware/i2c.h"
#include "Vec3f.hpp"

class IMU
{
public:
  IMU(bool autoZero);
  void read();
  void zero();
  float getRoll();
  float getPitch();
  float getRollVelocity();
  float getPitchVelocity();
  bool isAtRest();
  
private:
  i2c_inst_t *pHandle;
  Vec3f gyroVelReading;
  Vec3f presentedGyroVelReading;
  Vec3f gyroVelZero;
  Vec3f gyro;
  Vec3f presentedGyro;
  Vec3f accelReading;
  Vec3f accelGravity;
  float tempReading;
  uint64_t lastRead;
  bool autoZero;

  uint64_t getTimestampUs();
  void doRead();
};
