#include "MainMenu.hpp"

const char *MAIN_MENU_OPTIONS[] {
  "Select activity",
  "Overall statistics",
  "Options"
};

static const char **initActivityMenuItems(ActivityRegistry &activityReg)
{
  const char **pItems = new const char *[activityReg.getNumActivities() + 1];
  activityReg.getActivityNames(pItems);
  pItems[activityReg.getNumActivities()] = "Return";
  return pItems;
}

MainMenu::MainMenu(ActivityRegistry &activityReg, Inputs &inputs)
  : activityReg(activityReg),
    pSelectedActivity(nullptr),
    submenu(MAIN_MENU),
    mainMenu(inputs, 3, MAIN_MENU_OPTIONS),
    pActivityMenuItems(initActivityMenuItems(activityReg)),
    activityMenu(inputs, activityReg.getNumActivities(), pActivityMenuItems)
{ }

MainMenu::~MainMenu()
{
  delete[] pActivityMenuItems;
}

void MainMenu::tick()
{
  if (submenu == MAIN_MENU)
  {
    mainMenu.tick();
    switch (mainMenu.getSelection())
    {
    case 0:
      submenu = ACTIVITY_SELECT;
      break;
    case 1:
      submenu = DATA_ANALYSIS;
      break;
    case 2:
      submenu = GLOBAL_OPTIONS;
      break;
    }
  }
  else if (submenu == ACTIVITY_SELECT)
  {
    activityMenu.tick();
    int sel = activityMenu.getSelection();
    if (sel == activityReg.getNumActivities())
    {
      submenu = MAIN_MENU;
    }
    else if (sel != Menu::NOT_SELECTED)
    {
      pSelectedActivity = activityReg.getActivityByIndex(sel);
    }
  }
}

IActivity *MainMenu::getActivitySelection()
{
  IActivity *ret = pSelectedActivity;
  pSelectedActivity = nullptr;
  return ret;
}
