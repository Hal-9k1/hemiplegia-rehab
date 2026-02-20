#pragma once

#include "Config.hpp"
#include "Inputs.hpp"
#include "Activity.hpp"

class Program
{
public:
  Program();
  void tick();

private:
  Config conf;
  Inputs inputs;
  Activity *pCurrentActivity;
};
