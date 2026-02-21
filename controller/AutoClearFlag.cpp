#include "AutoClearFlag.hpp"

AutoClearFlag::AutoClearFlag()
  : flag(false)
{ }

bool AutoClearFlag::getAndClear()
{
  bool ret = flag;
  flag = false;
  return ret;
}

void AutoClearFlag::set()
{
  flag = true;
}
