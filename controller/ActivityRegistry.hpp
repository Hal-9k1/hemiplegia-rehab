#pragma once

#include "IActivity.hpp"

class ActivityRegistry
{
public:
  ActivityRegistry();
  ~ActivityRegistry();
  int getNumActivities();
  void getActivityNames(const char **pOut);
  IActivity *getActivityByIndex(int index);

private:
  IActivity **ppActivities;
  int numActivities;
  int loadingIdx;

  void loadActivities();
  template <typename T, typename... Args> void loadActivity(Args... args);
};
