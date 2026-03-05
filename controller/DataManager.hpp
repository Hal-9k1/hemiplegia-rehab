#pragma once

#include "IActivity.hpp"

/**
 * Retrieves and sets data recorded during activities across program runs.
 */
class DataManager
{
public:
  /**
   * Constructs a DataManager.
   */
  DataManager();

  /**
   * Saves data recorded during an activity.
   *
   * @param activity the activity to record data from.
   */
  void recordActivity(IActivity &activity);
};
