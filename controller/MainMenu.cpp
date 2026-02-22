#include "MainMenu.hpp"

const char *MAIN_MENU_OPTIONS[] {
  "Select activity",
  "Overall statistics",
  "Options"
};

MainMenu::MainMenu(ActivityRegistry &activityReg, Inputs &inputs)
  : activityReg(activityReg),
    selectedActivity(nullptr),
    submenu(MAIN_MENU),
    mainMenu(inputs, 3, MAIN_MENU_OPTIONS)
{ }

void MainMenu::tick()
{
  if (submenu == MAIN_MENU)
  {
    mainMenu.tick();
    switch (mainMenu.getSelection())
    {
    case Menu::NOT_SELECTED:
      break;
    case 0:
      subMenu = ACTIVITY_SELECT;
      break;
    case 1:
      subMenu = DATA_ANALYSIS;
      break;
    case 2:
      subMenu = GLOBAL_OPTIONS;
      break;
    }
  }
}
