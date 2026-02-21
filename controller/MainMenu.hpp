#pragma once

#include "Activity.hpp"

class MainMenu
{
public:
  MainMenu();
  void tick();
  Activity *getActivitySelection();
};
