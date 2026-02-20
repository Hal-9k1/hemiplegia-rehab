#include <cstdio>
#include "pico/stdlib.h"
#include "Program.hpp"

int main()
{
  Program prog;
  while (true)
  {
    prog.tick();
  }
  return 0;
}
