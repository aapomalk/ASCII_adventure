
#include "TurnSequence.h"
#include "Rubic.h"
#include <vector>
#include <iostream>

void TurnSequence::set_arr(const array<int, num_of_sides> &arr) {
  for (size_t i=0; i<num_of_sides && i<arr.size(); i++) {
    starts_and_ends.at(i) = arr.at(i);
  }
  this->update_turns();
}

void TurnSequence::update_turns() {
  for (auto &turn : this->turns) {
    turn = update_turn(turn);
  }
}

bool TurnSequence::update_arr(const SimpleTurn &t) {
  switch (t.get_a()) {
  case A1:
    if (this->starts_and_ends.at(0) != t.get_ps()
	|| this->starts_and_ends.at(1) != t.get_pe()) {
      this->starts_and_ends.at(0) = t.get_ps();
      this->starts_and_ends.at(1) = t.get_pe();
      return true;
    }
    return false;
  case A2:
    if (this->starts_and_ends.at(2) != t.get_ps()
	|| this->starts_and_ends.at(3) != t.get_pe()) {
      this->starts_and_ends.at(2) = t.get_ps();
      this->starts_and_ends.at(3) = t.get_pe();
      return true;
    }
    return false;
  case A3:
    if (this->starts_and_ends.at(4) != t.get_ps()
	|| this->starts_and_ends.at(5) != t.get_pe()) {
      this->starts_and_ends.at(4) = t.get_ps();
      this->starts_and_ends.at(5) = t.get_pe();
      return true;
    }
    return false;
  default:
    return false;
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

void TurnSequence::add_Turnable(SimpleTurn t) {
  this->turns.push_back(t);
  if (this->update_arr(t)) {
    this->update_turns();
  }
}

void TurnSequence::add_Turnables(const vector<SimpleTurn> &ts) {
  bool changed {false};
  for (auto t : ts) {
    turns.push_back(t);
    if (update_arr(t)) {
      changed = true;
    }
  }
  if (changed) {
    update_turns();
  }
}
