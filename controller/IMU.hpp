#pragma once

#include "hardware/i2c.h"
#include "Vec3f.hpp"

class IMU
{
public:
  IMU();
  void read();
  void zeroAtRest();
  float getRoll();
  float getPitch();
  float getRollVelocity();
  float getPitchVelocity();
  Vec3f getAccel();
  
private:
  i2c_inst_t *pHandle;
  Vec3f gyroVelReading;
  Vec3f gyroVelZero;
  Vec3f gyro;
  Vec3f accelReading;
  Vec3f accelGravity;
  float tempReading;
  uint64_t lastRead;

  uint64_t getTimestampUs();
};
