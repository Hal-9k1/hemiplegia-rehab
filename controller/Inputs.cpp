#include "Inputs.hpp"
#include <stdio.h>

Inputs::Inputs()
{ }

void Inputs::tick()
{
  int c = getchar();
  if (c == 'j')
  {
    menuDown.set();
  }
  else if (c == 'k')
  {
    menuUp.set();
  }
  else if (c == 'p')
  {
    pause.set();
  }
  else if (c == 'x')
  {
    menuSelect.set();
  }
}

bool Inputs::shouldPause()
{
  return pause.getAndClear();
}

bool Inputs::shouldMoveMenuUp()
{
  return menuUp.getAndClear();
}

bool Inputs::shouldMoveMenuDown()
{
  return menuDown.getAndClear();
}

bool Inputs::shouldSelectMenu()
{
  return menuSelect.getAndClear();
}
