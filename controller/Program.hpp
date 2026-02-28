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
  ActivityRegistry activityReg;
  MainMenu mainMenu;
  PauseMenu pauseMenu;
  Activity *pCurrentActivity;
  DataManager dataMgr;
};
