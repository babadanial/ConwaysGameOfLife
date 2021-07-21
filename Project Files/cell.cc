#include "subject.h"
#include "observer.h"
#include "cell.h"

#include <string>
#include <iostream>

using namespace std;

Cell::Cell() {}

bool Cell::getState() const { return isOn; }
int Cell::getRow() const { return r; }
int Cell::getCol() const { return c; }

void Cell::setOn() {
  if (!isOn) {
    isOn = true;
    notifyObservers(SubscriptionType::All);
  }
}

void Cell::toggle() {
  isOn = !isOn;

  notifyObservers(SubscriptionType::SwitchOnly);
  notifyObservers(SubscriptionType::All);
}

void Cell::setCoords(int row, int column) { 
  r = row; 
  c = column; 
}

void Cell::notify(Cell & whoNotified) {
  isOn = !isOn;
  notifyObservers(SubscriptionType::All);
}

void Cell::notifyObservers(SubscriptionType t) {
  int howMany = observers.size();
  for (int thisOne = 0; thisOne < howMany; ++thisOne) {
    Observer * thisObserver = observers[thisOne];
    if (thisObserver->subType() == t) {
      thisObserver->notify(*this);
    }
  }
}

SubscriptionType Cell::subType() const {
  return SubscriptionType::SwitchOnly;
}

string Cell::getName() const {
  string row = to_string(r);
  string column = to_string(c);
  string name = "(" + row + "," + column + ")";
  return name;
}

