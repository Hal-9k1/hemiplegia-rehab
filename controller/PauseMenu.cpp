#include "PauseMenu.hpp"

const static char *pOptions[]
{
  "Options",
  "Quit",
  "Continue"
};

PauseMenu::PauseMenu(Inputs &inputs)
  : pPausedActivityOptionsMenu(nullptr),
    menu(inputs, sizeof(pOptions) / sizeof(const char *), pOptions),
    showingOptions(false)
{ }

bool PauseMenu::isActive()
{
  return pPausedActivityOptionsMenu != nullptr;
}

bool PauseMenu::didUnpause()
{
  return unpaused.getAndClear();
}

bool PauseMenu::didQuit()
{
  return quit.getAndClear();
}

void PauseMenu::enable(IActivity &pausedActivity)
{
  pPausedActivityOptionsMenu = pausedActivity.getOptionsMenu();
}

void PauseMenu::tick()
{
  if (showingOptions && pPausedActivityOptionsMenu)
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
      pPausedActivityOptionsMenu = nullptr;
      break;
    }
  }
}
