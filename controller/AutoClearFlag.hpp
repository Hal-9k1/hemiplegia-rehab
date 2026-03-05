#pragma once

/**
 * Wraps a boolean flag that clears when read.
 */
class AutoClearFlag
{
public:
  /**
   * Constructs an AutoClearFlag.
   *
   * The flag is initially unset.
   */
  AutoClearFlag();

  /**
   * Returns the flag's value and sets it to false.
   *
   * @return the flag's value before being set to false.
   */
  bool getAndClear();

  /**
   * Sets the flag to true.
   */
  void set();

private:
  bool flag;
};
