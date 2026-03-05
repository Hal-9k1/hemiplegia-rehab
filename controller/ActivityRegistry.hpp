#pragma once

#include "IActivity.hpp"

/**
 * Registry of IActivities.
 *
 * @sa IActivity
 */
class ActivityRegistry
{
public:
  /**
   * Constructs an ActivityRegistry, registering a hardcoded list of activities.
   */
  ActivityRegistry();

  ~ActivityRegistry();

  /**
   * Returns the number of registered activities.
   *
   * @return the number of registered activities.
   */
  int getNumActivities();

  /**
   * Populates an array of activity names.
   *
   * @param pOut the array to be populated with activity display names. The array is assumed to have
   * enough capacity to store a number of strings equal to the return value of getNumActivities().
   */
  void getActivityNames(const char **pOut);

  /**
   * Access a registered activity by its index.
   *
   * @param index the index of activity to return. The index of an activity is
   * implementation-defined and may change between versions.
   *
   * @return the activity with the given @a index.
   */
  IActivity *getActivityByIndex(int index);

private:
  IActivity **ppActivities;
  int numActivities;
  int loadingIdx;

  void loadActivities();
  template <typename T, typename... Args> void loadActivity(Args... args);
};
