#pragma once

#include "Config.hpp"
#include "IOptionsMenu.hpp"

class IActivity
{
public:
  virtual void start(Config &conf) = 0;
  virtual void pause() = 0;
  virtual void unpause() = 0;
  virtual void tick() = 0;
  virtual bool didFinish() = 0;
  virtual IOptionsMenu *getOptionsMenu() = 0;
  virtual const char *getDisplayName() = 0;
};
