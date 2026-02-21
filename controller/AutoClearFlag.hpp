#pragma once

class AutoClearFlag
{
public:
  AutoClearFlag();
  bool getAndClear();
  void set();

private:
  bool flag;
};
