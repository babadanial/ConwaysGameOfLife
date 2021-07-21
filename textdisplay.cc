#include <iostream>
#include "textdisplay.h"
#include "subject.h"
#include "observer.h"
#include "cell.h"

using namespace std;

// for every row, we place one row into our theDisplay vector.
//    each row is a vector of chars the size of  gridSize (where
//    gridSize is both our grid's length AND width), with the elements
//    initialized to the '.' character, which represents a dead cell.
TextDisplay::TextDisplay(int n) : gridSize{n} {
  for (int row = 0; row < gridSize; ++row) {
    theDisplay.emplace_back(vector<char>(gridSize, '.'));
  }
}

void TextDisplay::notify(Cell &whoNotified) {
  // get the "Pixel" in the display for the corresponding Cell
  int row = whoNotified.getRow();
  int col = whoNotified.getCol();
  char * thePixel = &theDisplay.at(row).at(col);

  // and switch the character it displays to reflect the cell's alive
  //  status
  if (*thePixel == '.') {
    *thePixel = 'X';
  } else {
    *thePixel = '.';
  }
}

char TextDisplay::getCell(int row, int col) const {
  return theDisplay.at(row).at(col);
}

TextDisplay::~TextDisplay() {
  theDisplay.clear();
}

// TextDisplay subscribes to ALL events in a Cell, not just when
//  its life status switches
SubscriptionType TextDisplay::subType() const {
  return SubscriptionType::All;
}

std::string TextDisplay::getName() const {
  return "TD";
}

// prints out our graphical representation of every Cell in the Grid
//  using overloaded operator<<
ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int row = 0; row < td.gridSize; ++row) {
    for (int col = 0; col < td.gridSize; ++col) {
      cout << td.getCell(row, col);
    }
    cout << endl;
  }
  return out;
}

