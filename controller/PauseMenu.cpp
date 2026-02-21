#include "PauseMenu.hpp"

PauseMenu::PauseMenu()
  : active(false)
{ }

bool PauseMenu::isActive()
{
  return active;
}

bool PauseMenu::didUnpause()
{
  return paused.getAndClear();
}

bool PauseMenu::didQuit()
{
  return quit.getAndClear();
}

void PauseMenu::enable()
{
  active = true;
}

void PauseMenu::tick()
{
  // TODO
}
