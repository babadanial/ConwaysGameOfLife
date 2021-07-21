#include <iostream>
#include <string>
#include "grid.h"
#include <stdexcept>

using namespace std;

int main() {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd, aux;
  Grid g;
  int moves = 0;
  int row, col;

  while (true) {
    try {
      cin >> cmd;
      if (cmd == "new") {
        // read in size of the grid
        int n;
        cin >> n;

        // initialize the grid
        // note that we DO NOT call the constructor
        //    i.e. no line such as "g=Grid{}"
        g.init(n);
      }
      else if (cmd == "init") {
        cin >> row;
        cin >> col;

        while (!cin.fail()) {
          if ((row == -1) && (col == -1)) {
            // init "exit" command
            break;
          } else {
            g.turnOn(row, col);
          }
          // note we do not explicitly handle the case of invalid coordinates.

          cin >> row;
          cin >> col;
        }
        cout << g;
      }
      else if (cmd == "neighbours" ) {
        g.printCells();
      }
      else if (cmd == "game") {
        cin >> moves;

        // first print number of moves left if it isn't 0
        if (moves != 1) {
          cout << moves << " moves left" << endl;
        } else if (moves == 1) {
          cout << "1 move left" << endl;
        }

        // then check if the game is already in a winning state,
        //  and there are 0 moves left
        // this last part isn't truly necessary because "game 0" was
        //  not a valid test case, I just wanted to make it work for
        //  my own personal satisfaction
        if (g.isWon() && (moves == 0)) {
          cout << "Won" << endl;
          break;
        } else if (moves == 0) {
          cout << "Lost" << endl;
          break;
        }
      
      }
      else if (cmd == "switch") {
        // read in the coords of cell to toggle
        int r = 0, c = 0;
        cin >> r >> c;
        // toggle cell
        g.toggle(r, c);
        // show result
        cout << g;
        // decrement moves since we used one
        --moves;

        // first print number of moves left if it isn't 0
        if (moves != 1) {
          cout << moves << " moves left" << endl;
        } else if (moves == 1) {
          cout << "1 move left" << endl;
        }

        // then print win/loss status, especially if (moves == 0) (which is why it's the last case)
        if (g.isWon()) {
          cout << "Won" << endl;
          break;
        } else if (moves == 0) {
          cout << "Lost" << endl;
          break;
        }
      }
    }
    // handle exceptions from reading input
    catch (ios::failure &) {
      if (cin.eof()) {
        break;
      }
      cin.ignore();
      cin.clear();
    }
  }
}

