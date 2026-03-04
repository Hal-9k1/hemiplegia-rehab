#pragma once

#include "hardware/i2c.h"
#include "Vec3f.hpp"

/**
 * Controls the MPU-6050 IMU wired to the Pico.
 *
 * Only one instance should ever be constructed as the I2C block and pins are hardcoded.
 */
class IMU
{
public:
  /**
   * Constructs an IMU.
   *
   * @param autoZero if true, read() will call zero() if isAtRest() is true.
   */
  IMU(bool autoZero);

  /**
   * Reads the most recent IMU data.
   *
   * This function blocks, possibly as long as zero() blocks if auto-zeroing was enabled at
   * construction.
   */
  void read();

  /**
   * Zeroes the IMU in its current state.
   *
   * Saves averaged IMU readings over a long period as the zero reading; this zero reading will be
   * subtracted from subsequently returned readings.
   */
  void zero();

  /**
   * Returns the roll angle in degrees.
   *
   * @returns The roll angle in degrees. Greater positive values indicate rotation in the clockwise
   * direction (from the IMU's frame of reference.)
   */
  float getRoll();

  /**
   * Returns the pitch angle in degrees.
   *
   * @returns The roll angle in degrees. Greater positive values indicate rotation of the "nose" in
   * the upward direction (from the IMU's frame of reference.)
   */
  float getPitch();

  /**
   * Returns the roll velocity in degrees per second.
   *
   * @returns The roll velocity in degrees per second. See documentation for getRoll() for
   * explanation of direction.
   */
  float getRollVelocity();

  /**
   * Returns the pitch velocity in degrees per second.
   *
   * @returns The pitch velocity in degrees per second. See documentation for getPitch() for
   * explanation of direction.
   */
  float getPitchVelocity();

  /**
   * Heuristically determines whether the IMU is at rest.
   *
   * @returns Whether the IMU is determined to be at rest.
   */
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
