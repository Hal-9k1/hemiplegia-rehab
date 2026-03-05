#pragma once

#include "AutoClearFlag.hpp"

class Inputs
{
public:
  Inputs();
  void tick();
  bool shouldPause();
  bool shouldMoveMenuUp();
  bool shouldMoveMenuDown();
  bool shouldSelectMenu();

private:
  AutoClearFlag pause;
  AutoClearFlag menuUp;
  AutoClearFlag menuDown;
  AutoClearFlag menuSelect;
};
