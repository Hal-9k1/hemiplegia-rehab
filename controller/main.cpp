#include <cstdio>
#include "pico/stdio.h"
#include "pico/time.h"
#include "IMU.hpp"

bool reportAngle(repeating_timer_t *pTimer)
{
  IMU *pIMU = (IMU *)pTimer->user_data;
  printf(
    "Roll: %4.2f\tRoll vel: %4.2f\tPitch: %4.2f\tPitch vel: %4.2f\n",
    pIMU->getRoll(),
    pIMU->getRollVelocity(),
    pIMU->getPitch(),
    pIMU->getPitchVelocity()
  );
  return true;
}

int main()
{
  stdio_init_all();
  while (getchar_timeout_us(2 * 1000 * 1000) == PICO_ERROR_TIMEOUT)
  {
    printf("Press any key to begin\n");
  }
  printf("Start\n");
  repeating_timer_t timer;
  IMU imu(true);
  add_repeating_timer_ms(250, reportAngle, &imu, &timer);
  printf("Setup done\n");
  while (true)
  {
    imu.read();
  }
}
