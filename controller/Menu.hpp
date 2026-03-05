#pragma once

#include "Inputs.hpp"

class Menu
{
public:
  Menu(Inputs &inputs, int numOptions, const char **pOptions);
  void tick();
  int getCursorPos();
  int getSelection();
  void resetCursorPos();
  const static int NOT_SELECTED = -1;

private:

  Inputs &inputs;
  int numOptions;
  const char **pOptions;
  int cursor;
  int curSelection;
};
