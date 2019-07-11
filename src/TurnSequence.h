
#ifndef _TURN_SEQUENCE_H_
#define _TURN_SEQUENCE_H_

#include "Rubic.h"
#include <vector>
#include <iostream>

class TurnSequence {
  vector<int> starts_and_ends;
  vector<SimpleTurn> turns;
  SimpleTurn update_turn(const SimpleTurn &t) const;
 public:
 TurnSequence() : starts_and_ends(6, 0) {}
  void set_arr(const vector<int> &arr);
  void add_Turnable(const SimpleTurn &t);
  SimpleTurn get(int i) {return turns.at(i);}
  int size() {return turns.size();}
};

#endif
