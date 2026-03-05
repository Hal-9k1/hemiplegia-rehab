#include "Inputs.hpp"

Inputs::Inputs()
{ }

void Inputs::tick()
{
  // TODO: set flags from gpios
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
