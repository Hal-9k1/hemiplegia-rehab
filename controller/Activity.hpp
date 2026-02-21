#pragma once

#include "Config.hpp"

class Activity
{
public:
  Activity();
  void start(Config &conf);
  void pause();
  void unpause();
  void tick();
  bool didFinish();
};
