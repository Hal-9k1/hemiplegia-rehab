#pragma once

#include "IActivity.hpp"

class DataManager
{
public:
  DataManager();
  void recordActivity(IActivity &activity);
};
