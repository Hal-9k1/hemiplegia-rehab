#include "Menu.hpp"
#include <iostream>

Menu::Menu(Inputs &inputs, int numOptions, const char **pOptions)
  : inputs(inputs), numOptions(numOptions), pOptions(pOptions), cursor(0)
{ }

void Menu::tick()
{
  std::cout << "  " << pOptions[cursor] << std::endl;
  if (cursor > 0 && inputs.shouldMoveMenuUp())
  {
    --cursor;
  }
  else if (cursor < numOptions - 1 && inputs.shouldMoveMenuDown())
  {
    ++cursor;
  }
  if (inputs.shouldSelectMenu())
  {
    curSelection = cursor;
  }
}

int Menu::getCursorPos()
{
  return cursor;
}

int Menu::getSelection()
{
  int ret = curSelection;
  curSelection = NOT_SELECTED;
  return ret;
}

void Menu::resetCursorPos()
{
  cursor = 0;
}
