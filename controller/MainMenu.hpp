#pragma once

#include "Activity.hpp"
#include "Menu.hpp"

class MainMenu
{
public:
  MainMenu(ActivityRegistry &activityReg);
  void tick();
  Activity *getActivitySelection();

private:
  ActivityRegistry &activityReg;
  Activity *selectedActivity;
  Menu mainMenu;

  enum Submenu
  {
    MAIN_MENU,
    ACTIVITY_SELECT,
    DATA_ANALYSIS,
    GLOBAL_OPTIONS
  } submenu;
};
