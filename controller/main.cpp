#include <cstdio>
#include "pico/stdio.h"
#include "pico/time.h"
#include "Motor.hpp"

int main()
{
  stdio_init_all();
  while (getchar_timeout_us(2 * 1000 * 1000) == PICO_ERROR_TIMEOUT)
  {
    printf("Press any key to begin\n");
  }
  printf("Start\n");
  Motor motor(14, 15);
  printf("Setup done\n");
  while (true)
  {
    printf("Begin move\n");
    motor.move(400, 200);
    printf("Begin wait\n");
    motor.wait();
  }
}
