#include <iostream>
#include "grid.h"
#include "textdisplay.h"
#include "observer.h"
#include "cell.h"

using namespace std;

class TextDisplay;

Grid::Grid() {
  td = nullptr;
}

// prints the CONTENTS of the TextDisplay object held by the Grid
void Grid::printDisplay() const {
  cout << *td;
}

Grid::~Grid() { 
  delete td;
  clearGrid();
}

void Grid::clearGrid() { 
  theGrid.clear();
}

// checks whether the Grid is in winning/losing state if the game were
//  to end immediately, and updates the "won" parameter accordingly
void Grid::checkWinStatus() {
  bool success = 1;

  // iterates through the cells in the grid and checks if any are alive,
  //  in which case we break out of the loop and know for sure we are
  //  in a losing state
  for (int row = 0; row < gridSize; ++row) {
    for (int col = 0; col < gridSize; ++col) {
      if (theGrid.at(row).at(col).getState()) {
        success = 0;
        break;
      }
    }
    if (!success) { break; };
  }

  // and set the "won" parameter accordingly
  if (success) { 
    won = 1; 
  } else {
    won = 0;
  }
}

// simple accessor/getter
bool Grid::isWon() const { return won; }

void Grid::init(int n) {
  if (!theGrid.empty()) {
    clearGrid();
  }

  delete td;

  // setting Grid fields (containing state information)
  won = 1;
  td = new TextDisplay{n};
  gridSize = n;

  for (int row = 0; row < gridSize; ++row) {
    // creating a row of n Cells
    theGrid.emplace_back(vector<Cell>(n));
    for (int column = 0; column < gridSize; ++column) {
      // setting coords for each cell in the row
      (theGrid.at(row)).at(column).setCoords(row, column);
    }
  }

  // adding neighbours of each cell as Observers
  if (gridSize != 1) {
    for (int row = 0; row < gridSize; ++row) {
      for (int column = 0; column < gridSize; ++column) {
        // set a reference to the current cell for efficiency purposes
        //  i.e. do not have to repeat calls to .at every time we want
        //  to attach
        Cell & currentCell = (theGrid.at(row)).at(column);

        // the TextDisplay object must be an observer of the cell
        //  if it is to change its display values whenever the cell's
        //  "On" status changes
        currentCell.attach(td);

        if (row == 0) {
          // if cell is in first row, only attach cell below
          currentCell.attach(&((theGrid.at(row + 1)).at(column)));
        } else if (row == (gridSize - 1)) {
          // if cell is in last row, only attach cell above
          currentCell.attach(&((theGrid.at(row - 1)).at(column)));
        } else {
          // otherwise we are in a non-first/last row, and THUS the rows
          //  above and below should DEFINITELY exist 
          //  so, we add the cells below AND above
          currentCell.attach(&((theGrid.at(row + 1)).at(column)));
          currentCell.attach(&((theGrid.at(row - 1)).at(column)));
        } 
        
        if (column == 0) {
          // if cell is in the first column, only attach cell on the right
          currentCell.attach(&((theGrid.at(row)).at(column + 1)));
        } else if (column == (gridSize - 1)) {
          // if cell is in the last column, only attach cell on the left
          currentCell.attach(&((theGrid.at(row)).at(column - 1)));
        } else { 
          // otherwise we are in a non-first/last column, and THUS the columns
          //  to the right and left should DEFINITELY exist 
          //  so, we add the cells to the right AND to the left
          currentCell.attach(&((theGrid.at(row)).at(column + 1)));
          currentCell.attach(&((theGrid.at(row)).at(column - 1)));
        }
      }
    }
  } else {
    Cell & currentCell = (theGrid.at(0)).at(0);
    currentCell.attach(td);
  }
}

// turns on the Cell at (r,c) and immediately sets the "won" status
//    to off indirectly using checkWinStatus()
void Grid::turnOn(int r, int c) {
  theGrid.at(r).at(c).setOn();
  checkWinStatus();
}

// toggles the Cell at (r,c) on and off and immediately checks the "won"
//  status (in the event that this function turned the last "on" cell(s) 
//  off)
void Grid::toggle(int r, int c) {
  theGrid.at(r).at(c).toggle();
  checkWinStatus();
}

// grid output operator, overloaded, which really calls a helper
ostream &operator<<(ostream &out, const Grid &g) {
  g.printDisplay();
  return out;
}

// prints the neighbours of every Cell in the grid as part of the 
//  "neighbours" command
void Grid::printCells() const {
  for (int row = 0; row < gridSize; row++) {
    for (int column = 0; column < gridSize; column++) {
      Cell currentCell = (theGrid.at(row)).at(column);
      cout << currentCell.getName() << ": ";
      cout << currentCell.getObserverNames() << endl;
    }
  }
}

