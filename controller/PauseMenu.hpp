#pragma once

#include "IActivity.hpp"
#include "AutoClearFlag.hpp"
#include "Inputs.hpp"
#include "IOptionsMenu.hpp"
#include "Menu.hpp"

/**
 * Controls UI flow in the pause menu.
 */
class PauseMenu
{
public:
  /**
   * Constructs a PauseMenu.
   *
   * @param inputs the Inputs read to control the menu.
   */
  PauseMenu(Inputs &inputs);

  /**
   * Returns whether the menu should be shown.
   *
   * @return whether the menu should be shown based on previously received inputs and calls to
   * enable().
   */
  bool isActive();

  /**
   * Returns whether the menu was recently unpaused.
   *
   * @return whether isActive(), previously returning true, would now return false since the last
   * call to this method.
   */
  bool didUnpause();

  /**
   * Returns whether the presently running activity should be stopped and control returned to the
   * main menu.
   *
   * @return whether the user signaled to quit the presently running activity since the last call to
   * this method.
   */
  bool didQuit();

  /**
   * Shows the pause menu.
   *
   * @param pausedActivity the currently running activity.
   */
  void enable(IActivity &pausedActivity);

  /**
   * Updates the internal state of the menu.
   */
  void tick();

private:
  IOptionsMenu *pPausedActivityOptionsMenu;
  AutoClearFlag unpaused;
  AutoClearFlag quit;
  AutoClearFlag options;
  Menu menu;
  bool showingOptions;
};
