#pragma once

class PauseMenu
{
public:
  PauseMenu();
  bool isActive();
  bool didUnpause();
  bool didQuit();
  void enable();
  void tick();
};
