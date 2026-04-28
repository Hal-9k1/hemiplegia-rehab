#include <cstdio>
#include "pico/stdio.h"
#include "pico/time.h"
#include "Servo.hpp"

int main()
{
  stdio_init_all();
  while (getchar_timeout_us(2 * 1000 * 1000) == PICO_ERROR_TIMEOUT)
  {
    printf("Press any key to begin\n");
  }
  printf("Start\n");
  Servo servo(6, 1);
  printf("Setup done\n");
  float angle = 0;
  while (true)
  {
    servo.move(angle);
    angle += 0.5;
    sleep_ms(10);
    if (angle >= 180)
    {
      angle = 0;
      printf("at 180\n");
      sleep_ms(1000);
      servo.move(0);
      printf("reset\n");
      sleep_ms(1000);
    }
  }
}
