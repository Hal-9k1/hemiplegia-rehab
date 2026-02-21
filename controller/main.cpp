#include <cstdio>
#include "pico/stdio.h"
#include "pico/time.h"
#include "imu.hpp"

int main()
{
  stdio_init_all();
  while (true)
  {
    printf("Hello world!\n");
    sleep_ms(4002);
  }
}
