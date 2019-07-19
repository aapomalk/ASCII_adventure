
#ifndef _TURN_SEQUENCES_H_
#define _TURN_SEQUENCES_H_

#include "TurnSequence.h"
#include "Rubic.h"
#include <vector>
#include <iostream>
#include <memory>

class TurnSequences : public Turnable {
  vector<std::unique_ptr<TurnSequence>> turns;
  int total_size {0};
 public:
  void add_TurnSequence(std::unique_ptr<TurnSequence> ts){
    turns.push_back(std::move(ts));
    total_size += ts->size();
  }
  void set_arr(int i, const vector<int> &arr) {turns.at(i)->set_arr(arr);}
  int number_of_sequences() const {return turns.size();}
  virtual SimpleTurn get(int i) const override;
  virtual int size() const override {return total_size;}
};

#endif
