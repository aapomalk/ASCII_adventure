
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
  void addTurnable(const Turnable &t,bool mirror = false,bool reverse = false,
		   int size = 3) {
    if (reverse) {
      for (int i=t.size(); i>0; i--) {
	SimpleTurn temp = t.get(i-1);
	if (mirror) {
	  temp = temp.mirror(size);
	}
	if (reverse) {
	  temp = temp.reverse();
	}
	turns.push_back(temp);
      }
    } else {
      for (int i=0; i<t.size(); i++) {
	SimpleTurn temp = t.get(i);
	if (mirror) {
	  temp = temp.mirror(size);
	}
	turns.push_back(temp);
      }
    }
  }
};

class TurnSequence : public Turnable {
  array<int, num_of_sides> starts_and_ends;
  vector<SimpleTurn> turns;
  SimpleTurn update_turn(const SimpleTurn &t) const;
  void update_turns();
  bool update_arr(const SimpleTurn &t);
 public:
 TurnSequence() {
    starts_and_ends.fill(0);
  }
  void set_arr(const array<int, num_of_sides> &arr);
  void add_Turnable(SimpleTurn t);
  void add_Turnables(const vector<SimpleTurn> &ts);
  virtual SimpleTurn get(int i) const override {return turns.at(i);}
  virtual int size() const override {return turns.size();}
};

#endif
