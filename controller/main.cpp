#include <cstdio>
#include "pico/stdio.h"
#include "pico/time.h"
#include "Display.hpp"

int main()
{
  stdio_init_all();
  while (getchar_timeout_us(2 * 1000 * 1000) == PICO_ERROR_TIMEOUT)
  {
    printf("Press any key to begin\n");
  }
  printf("Start\n");
  int scroll = 0;
  int textWidth = getTextWidth("HELLO WORLD");

  Display display;
  while (true)
  {
    printf("Render\n");
    display.clearDisplay(); //adds pixels into the buffer rather than replacing them
    display.drawText(0, "HELLO WORLD", scroll);
    printf("Write\n");
    display.updateDisplay();
    scroll = (scroll + 1) % (textWidth + 32);
    printf("Sleep\n");
    sleep_ms(50);
  }
}
