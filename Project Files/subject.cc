#include <iostream>
#include "subject.h"
#include "observer.h"
#include <string>
#include <vector>

using namespace std;

class Observer;

void Subject::attach(Observer *o) {
   observers.push_back(o);
} // note that pointer to Observer will usually actually be a pointer
  //  to a Cell in this case

string Subject::getObserverNames() const {
   int numObservers = observers.size();
   vector<string> observerNames;
   for (int observer = 0; observer < numObservers; ++observer) {
      // retrieve name of Observers, one by one
      string thisName = observers.at(observer)->getName();

      if (observer == 0) { 
         // first observer name simply inserted, for efficiency
         observerNames.push_back(thisName);
      } else {             
         // otherwise, iterate through our sorted vector of observer names 
         //    until we find the right position in the vector to insert
         //    this Observer's name at
         // note "observer" counts which observer we are pulling from observers
         //    vector
         int sortingIterator = 0;
         while ((sortingIterator < observer) && !(thisName < observerNames.at   (sortingIterator))) {
            ++sortingIterator;
         }

         if (sortingIterator == observer) {
            // in case we got to the end of the sorted vector of observer names,
            //    just push to back for efficiency
            observerNames.push_back(thisName);
         } else {
            // otherwise, insert it at the right spot
            observerNames.insert(observerNames.begin() + sortingIterator, 
            thisName);
         }
      }
   }

   string total = "";
   int printingIterator = 0;
   while (printingIterator < numObservers) {
      // iterate through our sorted list of Observer names and add each 
      //    name to the "total" string of Observer names to be outputted

      string newName = observerNames.at(printingIterator);

      // and we only add a comma after the name of this observer if
      //    if it isn't the last one
      if (printingIterator != numObservers - 1) {
         newName += ", ";
      }

      // add this newName string to our total string of our observer names
      total += newName;
      // ...and move on to the next one
      ++printingIterator;
   }
   return total;
}