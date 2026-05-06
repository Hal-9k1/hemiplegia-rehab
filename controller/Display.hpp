#pragma once

class Display
{
public:
  Display();
  void defaultSettings(); // set the device’s brightness upon reboot
  void clearDisplay();
  void drawText(int row, const char *text, int scrollOffset); // should be able to process sentences
  void drawIcon(int x, int y, const char **iconData); // unsure for now as we’re not sure which icons we want to display
  void updateDisplay();
  int getTextWidth(const char *text);

private:
  void setPixel(int x, int y); //needed for drawtext
};
