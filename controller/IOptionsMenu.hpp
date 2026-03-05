#pragma once

/**
 * Interface for activity options menus.
 */
class IOptionsMenu
{
public:

  /**
   * Performs incremental work and updates the internal state of the menu.
   */
  virtual void tick() = 0;

  /**
   * Returns whether the options menu should presently be exited.
   *
   * @return whether the options menu was signaled to be exited since the last call to didReturn().
   */
  virtual bool didReturn() = 0;
};
