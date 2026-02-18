#include <cstdio>
#include "pico/stdlib.h"
#include "pico/time.h"

int main()
{
  stdio_init_all();
  while (true)
  {
    std::printf("Hello world!");
    sleep_ms(2000);
  }
}
