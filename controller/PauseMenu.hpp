#pragma once

#include "IActivity.hpp"
#include "AutoClearFlag.hpp"
#include "Inputs.hpp"
#include "IOptionsMenu.hpp"
#include "Menu.hpp"

class PauseMenu
{
public:
  PauseMenu(Inputs &inputs);
  bool isActive();
  bool didUnpause();
  bool didQuit();
  bool didOpenOptions();
  void enable(IActivity &pausedActivity);
  void tick();

private:
  IOptionsMenu *pPausedActivityOptionsMenu;
  AutoClearFlag unpaused;
  AutoClearFlag quit;
  AutoClearFlag options;
  Menu menu;
  bool showingOptions;
};
