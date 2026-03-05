#pragma once

#include "Inputs.hpp"

/**
 * Controls UI flow for a generic menu.
 *
 * Intended to be composed into objects representing specific menus.
 */
class Menu
{
public:
  /**
   * Constructs a Menu.
   *
   * @param inputs the Inputs read to control the menu.
   * @param numOptions the number of options in the menu.
   * @param pOptions the list of option texts in the menu.
   */
  Menu(Inputs &inputs, int numOptions, const char **pOptions);

  /**
   * Updates the internal state of the menu.
   */
  void tick();

  /**
   * Gets the index of the currently hovered menu item.
   *
   * @return the index of the currently hovered menu item.
   */
  int getCursorPos();

  /**
   * Gets the index of the presently selected menu item.
   *
   * @return the index of the menu item selected since the last call to this method, or NOT_SELECTED
   * if no item has been selected since then.
   */
  int getSelection();

  /**
   * Returns the cursor position to the first item.
   */
  void resetCursorPos();

  /**
   * The return value of getSelection() when no item has been selected since its last invocation.
   */
  const static int NOT_SELECTED = -1;

private:

  Inputs &inputs;
  int numOptions;
  const char **pOptions;
  int cursor;
  int curSelection;
};
