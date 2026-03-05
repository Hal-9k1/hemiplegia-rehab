#pragma once

#include "IActivity.hpp"
#include "ActivityRegistry.hpp"
#include "Config.hpp"
#include "DataManager.hpp"
#include "Inputs.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"

/**
 * Main class for the program, owning all state.
 */
class Program
{
public:
  /**
   * Constructs a Program.
   */
  Program();

  /**
   * Performs incremental work in the program.
   *
   * No expectations for call duration are established.
   */
  void tick();

private:
  Config conf;
  Inputs inputs;
  ActivityRegistry activityReg;
  MainMenu mainMenu;
  PauseMenu pauseMenu;
  IActivity *pCurrentActivity;
  DataManager dataMgr;
};
