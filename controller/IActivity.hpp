#pragma once

#include "Config.hpp"
#include "IOptionsMenu.hpp"

/**
 * Interface for rehabilitation programs/"activities".
 */
class IActivity
{
public:
  /**
   * Starts the activity.
   *
   * @param conf the persistent configuration used by the program.
   */
  virtual void start(Config &conf) = 0;

  /**
   * Pauses the activity, stopping any actuators.
   */
  virtual void pause() = 0;

  /**
   * Unpauses the activity.
   */
  virtual void unpause() = 0;

  /**
   * Performs incremental work and updates the internal state of the activity.
   */
  virtual void tick() = 0;

  /**
   * Returns whether the activity ended since the last call to start().
   */
  virtual bool didFinish() = 0;

  /**
   * Returns the activity-specific options menu.
   *
   * @return the activity-specific options menu.
   */
  virtual IOptionsMenu *getOptionsMenu() = 0;

  /**
   * Returns the display name of the activity.
   *
   * @return the display name of the activity.
   */
  virtual const char *getDisplayName() = 0;
};
