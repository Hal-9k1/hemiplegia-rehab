#pragma once

#include "IActivity.hpp"
#include "ActivityRegistry.hpp"
#include "Inputs.hpp"
#include "Menu.hpp"

class MainMenu
{
public:
  MainMenu(ActivityRegistry &activityReg, Inputs &inputs);
  ~MainMenu();
  void tick();
  IActivity *getActivitySelection();

private:
  ActivityRegistry &activityReg;
  IActivity *pSelectedActivity;
  Menu mainMenu;
  Menu activityMenu;
  const char **pActivityMenuItems;

  enum Submenu
  {
    MAIN_MENU,
    ACTIVITY_SELECT,
    DATA_ANALYSIS,
    GLOBAL_OPTIONS
  } submenu;
};
