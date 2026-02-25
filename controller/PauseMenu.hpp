#pragma once

#include "Activity.hpp"
#include "AutoClearFlag.hpp"
#include "IOptionsMenu.hpp"
#include "Menu.hpp"

class PauseMenu
{
public:
  PauseMenu();
  bool isActive();
  bool didUnpause();
  bool didQuit();
  bool didOpenOptions();
  void enable();
  void tick();

private:
  IOptionsMenu *pPausedActivityOptionsMenu;
  AutoClearFlag unpaused;
  AutoClearFlag quit;
  AutoClearFlag options;
  Menu menu;
};
