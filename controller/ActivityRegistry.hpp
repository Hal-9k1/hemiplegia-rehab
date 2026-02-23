#pragma once

#include "Activity.hpp"

class ActivityRegistry
{
public:
  ActivityRegistry();
  int getNumActivities();
  void getActivityNames(const char **pOut);
  Activity *getActivityByIndex();
};
