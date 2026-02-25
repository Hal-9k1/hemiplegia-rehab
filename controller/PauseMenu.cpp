#include "PauseMenu.hpp"

const static char *pOptions[]
{
  "Options",
  "Quit",
  "Continue"
};

PauseMenu::PauseMenu(Inputs &inputs)
  : active(false),
    menu(inputs, sizeof(pOptions) / sizeof(const char *), pOptions)
{ }

bool PauseMenu::isActive()
{
  return pPausedActivity != nullptr;
}

bool PauseMenu::didUnpause()
{
  return unpaused.getAndClear();
}

bool PauseMenu::didQuit()
{
  return quit.getAndClear();
}

void PauseMenu::enable(Activity *pCurrentActivity)
{
  pPausedActivityOptionsMenu = pPausedActivity->getOptionsMenu()
}

void PauseMenu::tick()
{
  if (showingOptions)
  {
    pPausedActivityOptionsMenu->tick();
    if (pPausedActivityOptionsMenu->didReturn())
    {
      showingOptions = false;
    }
  }
  else
  {
    menu.tick();
    switch (menu.getSelection())
    {
    case 0:
      showingOptions = true;
      break;
    case 1:
      quit.set();
      break;
    case 2:
      unpaused.set();
      break;
    }
  }
}
