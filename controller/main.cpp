#include <cstdio>
#include "pico/stdio.h"
#include "pico/time.h"
#include "IMU.hpp"

bool reportAngle(repeating_timer_t *pTimer)
{
  IMU *pIMU = (IMU *)pTimer->user_data;
  printf(
    "Roll: %.2f Roll vel: %.2f Pitch: %.2f Pitch vel: %.2f X accel: %.2f Y accel %.2f Z accel %.2f\n",
    pIMU->getRoll(),
    pIMU->getPitch(),
    pIMU->getRollVelocity(),
    pIMU->getPitchVelocity(),
    pIMU->getAccel().x,
    pIMU->getAccel().y,
    pIMU->getAccel().z
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
  IMU imu;
  add_repeating_timer_ms(250, reportAngle, &imu, &timer);
  printf("Setup done\n");
  while (true)
  {
    imu.read();
    sleep_us(50);
  }
}
