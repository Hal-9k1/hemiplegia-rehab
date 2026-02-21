#pragma once

#include "Activity.hpp"
#include "ActivityRegistry.hpp"
#include "Config.hpp"
#include "DataManager.hpp"
#include "Inputs.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"

class Program
{
public:
  Program();
  void tick();

private:
  Config conf;
  Inputs inputs;
  MainMenu mainMenu;
  PauseMenu pauseMenu;
  ActivityRegistry activityReg;
  Activity *pCurrentActivity;
  DataManager dataMgr;
};
