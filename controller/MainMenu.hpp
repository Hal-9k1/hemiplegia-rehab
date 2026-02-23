#pragma once

#include "Activity.hpp"
#include "Menu.hpp"

class MainMenu
{
public:
  MainMenu(ActivityRegistry &activityReg);
  ~MainMenu();
  void tick();
  Activity *getActivitySelection();

private:
  ActivityRegistry &activityReg;
  Activity *pSelectedActivity;
  Menu mainMenu;
  Menu activityMenu;

  enum Submenu
  {
    MAIN_MENU,
    ACTIVITY_SELECT,
    DATA_ANALYSIS,
    GLOBAL_OPTIONS
  } submenu;
};
