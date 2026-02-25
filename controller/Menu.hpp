#pragma once

class Menu
{
public:
  Menu(Inputs &inputs, int numOptions, const char **pOptions);
  void tick();
  int getCursorPos();
  int getSelection();
  void resetCursorPos();

private:
  const static int NOT_SELECTED = -1;

  Inputs &inputs;
  int numOptions;
  const char **pOptions;
  int cursor;
  int curSelection;
};
