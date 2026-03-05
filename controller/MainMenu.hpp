#pragma once

#include "IActivity.hpp"
#include "ActivityRegistry.hpp"
#include "Inputs.hpp"
#include "Menu.hpp"

/**
 * Controls UI flow in the main menu.
 */
class MainMenu
{
public:
  /**
   * Constructs a MainMenu.
   *
   * @param activityReg the ActivityRegistry whose registered activities will be displayed as menu
   * items in the activity selection submenu.
   * @param inputs the Inputs read to control the menu.
   */
  MainMenu(ActivityRegistry &activityReg, Inputs &inputs);

  ~MainMenu();

  /**
   * Updates the internal state of the menu.
   */
  void tick();

  /**
   * Returns the activity that should presently be started.
   *
   * @return the activity selected by the user since the last call to this method, or nullptr if
   * the user has not selected an activity since then.
   */
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
