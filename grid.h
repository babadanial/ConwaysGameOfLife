#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "cell.h"
#include "textdisplay.h"

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  int gridSize;          // Size of the grid.
  bool won;              // Grid in winning state
  TextDisplay *td;       // The text display.
  // Add private members, if necessary.
  void checkWinStatus(); // Checks if the game has been won.
  void clearGrid();      // Frees the grid.

 public:
  Grid();
  ~Grid();

  bool isWon() const; // Call to determine if grid is in a winning state.
  void init(int n); // Sets up an n x n grid.  Clears old grid, if necessary.
  void turnOn(int r, int c);  // Sets cell at row r, col c to On.
  void toggle(int r, int c);  // Toggles cell at row r, col c from On/Off to Off/On.
  void printDisplay() const; // Prints the Text Display
  void printCells() const; // Prints out each cell and their neighbours
  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif

