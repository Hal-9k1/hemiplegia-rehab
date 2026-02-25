#pragma once

class Inputs
{
public:
  Inputs();
  void tick();
  bool shouldPause();
  bool shouldMoveMenuUp();
  bool shouldMoveMenuDown();
  bool shouldSelectMenu();
};
