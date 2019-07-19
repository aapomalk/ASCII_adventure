
#ifndef _TURN_SEQUENCE_H_
#define _TURN_SEQUENCE_H_

#include "Rubic.h"
#include <vector>
#include <iostream>

class Turnable {
 public:
  virtual SimpleTurn get(int) const = 0;
  virtual int size() const = 0;
  virtual ~Turnable() = default;
};

struct TurnVector : public Turnable {
  vector<SimpleTurn> turns;
  virtual int size() const override {return turns.size();}
  virtual SimpleTurn get(int i) const override {return turns.at(i);}
};

class TurnSequence : public Turnable {
  vector<int> starts_and_ends;
  vector<SimpleTurn> turns;
  SimpleTurn update_turn(const SimpleTurn &t) const;
  void update_turns();
  bool update_arr(const SimpleTurn &t);
 public:
 TurnSequence() : starts_and_ends(6, 0) {}
  void set_arr(const vector<int> &arr);
  void add_Turnable(SimpleTurn t);
  void add_Turnables(const vector<SimpleTurn> &ts);
  virtual SimpleTurn get(int i) const override {return turns.at(i);}
  virtual int size() const override {return turns.size();}
};

#endif
