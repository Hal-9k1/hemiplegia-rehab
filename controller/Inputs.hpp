#pragma once

#include "AutoClearFlag.hpp"

/**
 * Manages the capture of user input.
 */
class Inputs
{
public:
  /**
   * Constructs an Inputs.
   */
  Inputs();

  /**
   * Performs incremental work and updates the state of the Inputs object.
   */
  void tick();

  /**
   * Returns whether a presently running activity should be paused.
   *
   * @return whether the input bound to pause activities has been activated since the last call to a
   * method that checks its state.
   */
  bool shouldPause();

  /**
   * Returns whether a presently open menu should move the cursor up.
   *
   * @return whether the input bound to move the cursor up in menus has been activated since the
   * last call to a method that checks its state.
   */
  bool shouldMoveMenuUp();

  /**
   * Returns whether a presently open menu should move the cursor down.
   *
   * @return whether the input bound to move the cursor down in menus has been activated since the
   * last call to a method that checks its state.
   */
  bool shouldMoveMenuDown();

  /**
   * Returns whether a presently open menu should select the menu item under the cursor.
   *
   * @return whether the input bound to select items in menus has been activated since the last call
   * to a method that checks its state.
   */
  bool shouldSelectMenu();

private:
  AutoClearFlag pause;
  AutoClearFlag menuUp;
  AutoClearFlag menuDown;
  AutoClearFlag menuSelect;
};
