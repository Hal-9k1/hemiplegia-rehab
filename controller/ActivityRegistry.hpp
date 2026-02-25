#pragma once

#include "Activity.hpp"

class ActivityRegistry
{
public:
  ActivityRegistry();
  ~ActivityRegistry();
  int getNumActivities();
  void getActivityNames(const char **pOut);
  Activity *getActivityByIndex(int index);

private:
  Activity *pActivities;
  int numActivities;
  int loadingIdx;

  void loadActivities();
  template <typename T, typename... Args> void loadActivity(Args... args);
};
