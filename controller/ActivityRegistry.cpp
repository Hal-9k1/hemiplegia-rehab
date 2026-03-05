#include "ActivityRegistry.hpp"

ActivityRegistry::ActivityRegistry()
  : ppActivities(nullptr)
{
  loadActivities();
  numActivities = loadingIdx;
  loadingIdx = 0;
  ppActivities = new IActivity *[numActivities];
  loadActivities();
}

ActivityRegistry::~ActivityRegistry()
{
  delete[] ppActivities;
}

int ActivityRegistry::getNumActivities()
{
  return numActivities;
}

void ActivityRegistry::getActivityNames(const char **pOut)
{
  for (int i = 0; i < numActivities; ++i)
  {
    pOut[i] = ppActivities[i]->getDisplayName();
  }
}

IActivity *ActivityRegistry::getActivityByIndex(int index)
{
  return ppActivities[index];
}

void ActivityRegistry::loadActivities()
{

}

template <typename T, typename... Args>
void ActivityRegistry::loadActivity(Args... args)
{
  if (ppActivities)
  {
    ppActivities[loadingIdx] = new T(args...);
  }
  loadingIdx++;
}
