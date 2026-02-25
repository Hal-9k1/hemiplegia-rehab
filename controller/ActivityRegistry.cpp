#include "ActivityRegistry.hpp"

ActivityRegistry::ActivityRegistry()
  : pActivities(nullptr)
{
  loadActivities();
  numActivities = loadingIdx;
  loadingIdx = 0;
  pActivities = new Activity *[numActivities];
  loadActivities();
}

ActivityRegistry::~ActivityRegistry()
{
  delete[] pActivities;
}

int ActivityRegistry::getNumActivities()
{
  return numActivities;
}

void ActivityRegistry::getActivityNames(const char **pOut)
{
  for (int i = 0; i < numActivities; ++i)
  {
    pOut[i] = pActivities[i].getDisplayName();
  }
}

Activity *ActivityRegistry::getActivityByIndex(int index)
{
  return pActivities + index;
}

void ActivityRegistry::loadActivities()
{

}

template <typename T, typename... Args>
void ActivityRegistry::loadActivity(Args... args)
{
  if (pActivities)
  {
    new (pActivities + loadingIdx) T(...);
  }
  loadingIdx++;
}
