#pragma once

class IOptionsMenu
{
public:
  virtual void tick() = 0;
  virtual bool didReturn() = 0;
};
