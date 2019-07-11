
#include "TurnSequence.h"
#include "Rubic.h"
#include <vector>
#include <iostream>

void TurnSequence::set_arr(const vector<int> &arr) {
  for (size_t i=0; i<6 && i<arr.size(); i++) {
    if (i<starts_and_ends.size()) {
      starts_and_ends.at(i) = arr.at(i);
    } else {
      starts_and_ends.push_back(arr.at(i));
    }
  }
}

SimpleTurn TurnSequence::update_turn(const SimpleTurn &t) const { 
  int start;
  int end;
  switch (t.get_a()) {
  case A1:
    start = this->starts_and_ends.at(0);
    end = this->starts_and_ends.at(1);
    break;
  case A2:
    start = this->starts_and_ends.at(2);
    end = this->starts_and_ends.at(3);
    break;
  case A3:
    start = this->starts_and_ends.at(4);
    end = this->starts_and_ends.at(5);
    break;
  default:
    // nothing happens
    return SimpleTurn{t.get_a(), t.get_t(), t.get_ps(), t.get_pe()};
  }
  SimpleTurn temp {t.get_a(), t.get_t(), start, end};
  return temp;
}

void TurnSequence::add_Turnable(const SimpleTurn &t) {
  this->turns.push_back(update_turn(t));
}
