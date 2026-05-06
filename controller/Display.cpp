#include "Display.hpp"

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "font.hpp"

#define PIN_MOSI 3
#define PIN_SCK 2
#define PIN_CS 5
#define NUM_MODULES 4
#define SPI_BLOCK spi0

uint8_t displayBuffer[8][NUM_MODULES] = {0};

static void max7219_LEDcontrol(uint8_t reg, uint8_t data) {
  gpio_put(PIN_CS, 0);
  for (int count = 0; count < NUM_MODULES; count++) {
    uint8_t buf[2] = {reg, data}; // (fixed uint 8_t)
    spi_write_blocking(SPI_BLOCK, buf, 2);
  }
  gpio_put(PIN_CS, 1);
}


static void max7219_send_command_diff(uint8_t reg, uint8_t value[NUM_MODULES]) {
  gpio_put(PIN_CS, 0);
  for (int count = 0; count < NUM_MODULES; count++) {
    uint8_t buf[2] = {reg, value[count]}; // (fixed values typo)
    spi_write_blocking(SPI_BLOCK, buf, 2);
  }
  gpio_put(PIN_CS, 1);
}

Display::Display() {
  gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
  gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
}

void Display::defaultSettings() {
  max7219_LEDcontrol(0x0C, 0x01); //wake up display
  max7219_LEDcontrol(0x0B, 0x07); //uses all 8 rows
  max7219_LEDcontrol(0x09, 0x00); //we are using custom font
  max7219_LEDcontrol(0x0A, 0x08); //set brightness
  max7219_LEDcontrol(0x0F, 0x00); //turn off display
}


void Display::clearDisplay() {
  for (int r = 0; r < 8; r++) {
    for (int m = 0; m < NUM_MODULES; m++) {
      displayBuffer[r][m] = 0;
    }
  }
}


void Display::updateDisplay() {
  for (int r = 0; r < 8; r++) {
    max7219_send_command_diff(r+1, displayBuffer[r]);
  }
}

//—---------------Pixel—----------------------
void Display::setPixel(int x, int y) {
  int module = x/8;
  int col = x % 8;

  if (module >= NUM_MODULES) return;
  if (y < 0 || y >= 8) return;

  uint8_t bit = (0b10000000 >> col);

  displayBuffer[y][module] |= bit;
}


//—---------REAL PART—----------------
void Display::drawText(int row, const char *text, int scrollOffset){
  int cursorX = 0;
  while (*text) {
    char c = *text;
    int index = -1;

    //word spacing
    if (c == ' ') {
      cursorX += 2;
      text++;
      continue;
    }

    //actual font
    if (c >= 'A' && c <= 'Z') {
      index = c - 'A';
    }
    else if (c >= '0' && c <= '9') {
      index = (c - '0') + 26;
    }
    else if (c == '!') index = 36;
    else if (c == '?') index = 37;
    else if (c == '.') index = 38;
    else if (c == ':') index = 39;
    else if (c == '-') index = 40;
    else if (c == '(') index = 41;
    else if (c == ')') index = 42;
    else if (c == '<') index = 43;
    else if (c == '>') index = 44;

    int width = 3; // default
    if (index == ('M' - 'A')) width = 4;
    else if (index == ('N' - 'A')) width = 4;
    else if (index == ('W' - 'A')) width = 5;


    if (index != -1){
      for (int col = 0; col < width; col++){
        if (cursorX + col - scrollOffset >=  0 && cursorX + col - scrollOffset < 32) {
          for (int r = 0; r < 8; r++) {
            uint8_t rowData = font[index][r];
            if (rowData & (0b10000000 >> col)){
              setPixel(cursorX + col - scrollOffset, row + r);
            }
          }
        }
      }
      cursorX += width; // letter width
      cursorX += 1; // 1-column gap
    }
    text++;
  }
}

void Display::drawIcon(int x, int y, const char **iconData) {

}

int Display::getTextWidth(const char *text)
{
  int widthTotal = 0;
  while (*text)
  {
    char c = *text;
    int index = -1;

    if (c == ' ')
    {
      widthTotal += 2;
      text++;
      continue;
    }
    if (c >= 'A' && c <= 'Z') index = c - 'A';
    else if (c >= '0' && c <= '9') index = (c - '0') + 26;
    else if (c == '!') index = 36;
    else if (c == '?') index = 37;
    else if (c == '.') index = 38;
    else if (c == ':') index = 39;
    else if (c == '-') index = 40;
    else if (c == '(') index = 41;
    else if (c == ')') index = 42;
    else if (c == '<') index = 43;
    else if (c == '>') index = 44;

    if (index != -1)
    {
      int w = 3;
      if (index == ('M' - 'A') || index == ('N' - 'A')) w = 4;
      else if (index == ('W' - 'A')) w = 5;

      widthTotal += w;
      widthTotal += 1; // letter gap
    }
    text++;
  }
  return widthTotal;
}
