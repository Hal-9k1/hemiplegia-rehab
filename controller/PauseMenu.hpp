#pragma once

#include "AutoClearFlag.hpp"

class PauseMenu
{
public:
  PauseMenu();
  bool isActive();
  bool didUnpause();
  bool didQuit();
  void enable();
  void tick();

private:
  bool active;
  AutoClearFlag paused;
  AutoClearFlag quit;
};
