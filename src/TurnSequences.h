
#ifndef _TURN_SEQUENCES_H_
#define _TURN_SEQUENCES_H_

#include "TurnSequence.h"
#include "Rubic.h"
#include <vector>
#include <iostream>

class TurnSequences : public Turnable {
  vector<TurnSequence> turns;
  int total_size {0};
 public:
  void add_TurnSequence(TurnSequence ts, bool reverse = false,
						bool mirror = false, int size = 0);
  void set_arr(int i, const vector<int> &arr) {turns.at(i).set_arr(arr);}
  int number_of_sequences() const {return turns.size();}
  virtual SimpleTurn get(int i) const override;
  virtual int size() const override {return total_size;}
};

#endif
