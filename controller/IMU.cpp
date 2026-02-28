#include "imu.hpp"

#include <climits>
#include <cmath>
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/time.h"
#include <cstdio>

#define I2C_ADDRESS 0x68
#define CONF_REG_ADDR 0x1B
#define ACCEL_SCALE_NUM 1 // [0, 4], increase -> more range less precision
#define GYRO_SCALE_NUM 1
#define NUM_SENSOR_REGISTERS 6 // accel x/y/z, temp, gyro x/y
#define ACCEL_SCALE (2 << ACCEL_SCALE_NUM) // g force
#define GYRO_SCALE (125 * (2 << GYRO_SCALE_NUM)) // deg/s
#define I2C_HANDLE i2c_default

const static uint8_t SENSOR_REG_ADDR = 0x3B;

IMU::IMU()
{
  i2c_init(I2C_HANDLE, 100 * 1000);
  gpio_set_function(4, GPIO_FUNC_I2C);
  gpio_set_function(5, GPIO_FUNC_I2C);
  gpio_pull_up(4);
  gpio_pull_up(5);
  lastRead = getTimestampUs();
  gyroVelReading.z = 0; // we never read this
  zeroAtRest();
  uint8_t configWrite[] { CONF_REG_ADDR, GYRO_SCALE_NUM << 2, ACCEL_SCALE_NUM << 2 };
  i2c_write_blocking(I2C_HANDLE, I2C_ADDRESS, configWrite, 3, true);
}

void IMU::read()
{
  uint64_t now = getTimestampUs();
  i2c_write_blocking(I2C_HANDLE, I2C_ADDRESS, &SENSOR_REG_ADDR, 1, true);
  uint8_t buf[NUM_SENSOR_REGISTERS * 2];
  i2c_read_blocking(I2C_HANDLE, I2C_ADDRESS, buf, NUM_SENSOR_REGISTERS * 2, true);
  float regVals[NUM_SENSOR_REGISTERS];
  for (int i = 0; i < NUM_SENSOR_REGISTERS; ++i)
  {
    regVals[i] = (float)((int)buf[i * 2] << 8 | buf[i * 2 + 1] - 0x8000);
  }
  accelReading.x = regVals[0] * ACCEL_SCALE / UINT16_MAX;
  accelReading.y = regVals[1] * ACCEL_SCALE / UINT16_MAX;
  accelReading.z = regVals[2] * ACCEL_SCALE / UINT16_MAX;
  printf("Accel {%.2f, %.2f, %.2f}\n", accelReading.x, accelReading.y, accelReading.z);
  tempReading = regVals[3] / 340 + 36.53; // see register map
  gyroVelReading.x = regVals[4] * GYRO_SCALE / UINT16_MAX - gyroVelZero.x;
  gyroVelReading.y = regVals[5] * GYRO_SCALE / UINT16_MAX - gyroVelZero.y;
  printf("Gyro {%.2f, %.2f}\n", gyroVelReading.x, gyroVelReading.y);
  gyro = gyro + gyroVelReading * (now - lastRead) / 1000000;
  lastRead = now;
}

void IMU::zeroAtRest()
{
  gyroVelZero = {0, 0};
  read();
  gyroVelZero = gyroVelReading;
  accelGravity = accelReading;
  printf("Recorded {%.2f, %.2f, %.2f} as gravity\n", accelGravity.x, accelGravity.y, accelGravity.z);
  gyro.x = atan2f(accelGravity.z, accelGravity.y);
  gyro.y = atan2f(accelGravity.z, -accelGravity.x);
}

float IMU::getRoll()
{
  // greater roll = clockwise roll
  return gyro.y;
}

float IMU::getPitch()
{
  // greater pitch = nose pointing up
  return gyro.x;
}

float IMU::getRollVelocity()
{
  return gyroVelReading.y;
}

float IMU::getPitchVelocity()
{
  return gyroVelReading.x;
}

Vec3f IMU::getAccel()
{
  return accelReading - accelGravity;
}

uint64_t IMU::getTimestampUs()
{
  return to_us_since_boot(get_absolute_time());
}
