#include "imu.hpp"

#include <climits>
#include <cmath>
#include <cstdio>
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pico/time.h"
#include "Vec3f.hpp"

#define I2C_ADDRESS 0x68
#define CONF_REG_ADDR 0x1A
#define SENSOR_REG_ADDR 0x3B
#define ID_REG_ADDR 0x75
#define POWER_MGMT_ADDR 0x6B
#define ACCEL_SCALE_NUM 1 // [0, 4], increase -> more range less precision
#define GYRO_SCALE_NUM 3
#define NUM_SENSOR_REGISTERS 6 // accel x/y/z, temp, gyro x/y
#define ACCEL_SCALE (2 << ACCEL_SCALE_NUM) // g force
#define GYRO_SCALE (125 * (2 << GYRO_SCALE_NUM)) // deg/s
#define I2C_HANDLE i2c_default
#define DLPF_CONFIG_VALUE 6 // ~5Hz bandwidth, ~19ms reading delay
#define NUM_ZERO_AVERAGES 32
#define ZERO_AVERAGE_PERIOD 200 // ms
#define INIT_ZERO_DELAY 100 // ms
#define GRAV_MAG_REST_THRESHOLD 0.05
#define GYRO_VEL_MAG_REST_THRESHOLD 0.7
#define GYRO_VEL_SQMAG_REST_THRESHOLD (GYRO_VEL_MAG_REST_THRESHOLD * GYRO_VEL_MAG_REST_THRESHOLD)

static bool writeI2C(uint8_t *pBuf, int size);
static bool readI2C(uint8_t *pBuf, int size);
static bool readReg(uint8_t addr, uint8_t *pBuf, int size);

IMU::IMU(bool autoZero)
  : presentedGyro{0, 0, 0},
    presentedGyroVelReading{0, 0, 0},
    autoZero(autoZero)
{
  i2c_init(I2C_HANDLE, 100 * 1000);
  gpio_set_function(4, GPIO_FUNC_I2C);
  gpio_set_function(5, GPIO_FUNC_I2C);
  gpio_pull_up(4);
  gpio_pull_up(5);
  uint8_t idReg = 0;
  readReg(ID_REG_ADDR, &idReg, 1);
  printf("Read id: %x\n", idReg);
  if (idReg != I2C_ADDRESS)
  {
    printf("I2C read sanity check failed!\n");
  }
  uint8_t configWrite[] {
    CONF_REG_ADDR,
    DLPF_CONFIG_VALUE,
    GYRO_SCALE_NUM << 2,
    ACCEL_SCALE_NUM << 2
  };
  writeI2C(configWrite, sizeof(configWrite));
  uint8_t powerWrite[] { POWER_MGMT_ADDR, 0 };
  writeI2C(powerWrite, sizeof(powerWrite));
  gyroVelReading.z = 0; // we never read this
  lastRead = getTimestampUs();
  sleep_ms(INIT_ZERO_DELAY);
  zero();
}

void IMU::read()
{
  if (autoZero && isAtRest())
  {
    zero();
  }
  else
  {
    doRead();
  }
  presentedGyroVelReading = gyroVelReading;
  presentedGyro = gyro;
}

void IMU::doRead()
{
  uint8_t buf[NUM_SENSOR_REGISTERS * 2];
  float regVals[NUM_SENSOR_REGISTERS];
  uint64_t now = getTimestampUs();
  readReg(SENSOR_REG_ADDR, buf, sizeof(buf));
  for (int i = 0; i < NUM_SENSOR_REGISTERS; ++i)
  {
    int reg16 = buf[i * 2] << 8 | buf[i * 2 + 1];
    if (reg16 & 0x8000)
    {
      reg16 = -(~reg16 & 0x7FFF);
    }
    regVals[i] = (float)reg16;
  }
  accelReading.x = regVals[0] * ACCEL_SCALE / UINT16_MAX;
  accelReading.y = regVals[1] * ACCEL_SCALE / UINT16_MAX;
  accelReading.z = regVals[2] * ACCEL_SCALE / UINT16_MAX;
  tempReading = regVals[3] / 340 + 36.53; // see register map for temp scaling values
  gyroVelReading.x = regVals[4] * GYRO_SCALE / UINT16_MAX - gyroVelZero.x;
  gyroVelReading.y = regVals[5] * GYRO_SCALE / UINT16_MAX - gyroVelZero.y;
  gyro = gyro + gyroVelReading * (now - lastRead) / 1000000;
  lastRead = now;
}

void IMU::zero()
{
  printf("Zeroing\n");
  gyroVelZero = {0, 0, 0};
  Vec3f sumAccel{0, 0, 0};
  Vec3f sumGyro{0, 0, 0};
  for (int i = 0; i < NUM_ZERO_AVERAGES; ++i)
  {
    doRead();
    sumAccel += accelReading;
    sumGyro += gyroVelReading;
    if (i != NUM_ZERO_AVERAGES - 1)
    {
      sleep_ms(ZERO_AVERAGE_PERIOD / NUM_ZERO_AVERAGES);
    }
  }
  gyroVelZero = sumGyro / NUM_ZERO_AVERAGES;
  accelGravity = sumAccel / NUM_ZERO_AVERAGES;
  gyro.x = atan2f(accelGravity.z, accelGravity.y);
  gyro.y = atan2f(accelGravity.z, -accelGravity.x);
}

float IMU::getRoll()
{
  // greater roll = clockwise roll
  return presentedGyro.y;
}

float IMU::getPitch()
{
  // greater pitch = nose pointing up
  return presentedGyro.x;
}

float IMU::getRollVelocity()
{
  return presentedGyroVelReading.y;
}

float IMU::getPitchVelocity()
{
  return presentedGyroVelReading.x;
}

uint64_t IMU::getTimestampUs()
{
  return to_us_since_boot(get_absolute_time());
}

bool IMU::isAtRest()
{
  float gravMagDiff = fabs(sqrtf(accelReading.sqLen()) - sqrtf(accelGravity.sqLen()));
  float gyroVelSqMag = gyroVelReading.sqLen();
  //printf("gravMagDiff %4.2f\tcosGravAngleDiff %4.2f\tgyroVelSqMag %4.2f\n", gravMagDiff, cosGravAngleDiff, gyroVelSqMag);
  return gravMagDiff < GRAV_MAG_REST_THRESHOLD
    && gyroVelSqMag < GYRO_VEL_SQMAG_REST_THRESHOLD;
}

static bool writeI2C(uint8_t *pBuf, int size)
{
  int res = i2c_write_blocking(I2C_HANDLE, I2C_ADDRESS, pBuf, size, false);
  if (res == size)
  {
    return true;
  }
  else if (res == PICO_ERROR_GENERIC)
  {
    printf("Write from IMU failed: no response\n");
  }
  else
  {
    printf("Write from IMU failed: premature end\n");
  }
  return false;
}

static bool readI2C(uint8_t *pBuf, int size)
{
  int res = i2c_read_blocking(I2C_HANDLE, I2C_ADDRESS, pBuf, size, false);
  if (res == size)
  {
    return true;
  }
  else if (res == PICO_ERROR_GENERIC)
  {
    printf("Read from IMU failed: no response\n");
  }
  else
  {
    printf("Read from IMU failed: premature end\n");
  }
  return false;
}

static bool readReg(uint8_t addr, uint8_t *pBuf, int size)
{
  return writeI2C(&addr, 1) && readI2C(pBuf, size);
}
