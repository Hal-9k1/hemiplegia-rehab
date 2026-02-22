#include <cstdio>
#include "pico/stdio.h"
#include "pico/time.h"
#include "IMU.hpp"

bool reportAngle(repeating_timer_t *pTimer)
{
  IMU *pIMU = (IMU *)pTimer->user_data;
  printf("Roll: %.2f Pitch: %2.f\n", pIMU->getRoll(), pIMU->getPitch());
  return true;
}

int main()
{
  stdio_init_all();
  repeating_timer_t timer;
  IMU imu;
  add_repeating_timer_ms(250, reportAngle, &imu, &timer);
  while (true)
  {
    imu.read();
    sleep_us(50);
  }
}
