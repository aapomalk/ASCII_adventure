
#include "TurnSequence.h"
#include "TurnSequences.h"
#include <stdexcept>

void TurnSequences::add_TurnSequence(TurnSequence ts, bool reverse, bool mirror,
									 int size) {
  if (mirror == false && reverse == false) {
	turns.push_back(ts);
  } else {
	TurnSequence temp;
	if (reverse) {
	  for (int i = ts.size(); i>0; i--) {
		SimpleTurn st = ts.get(i-1).reverse();
		if (mirror) {
		  st = st.mirror(size);
		}
	    temp.add_Turnable(st);
	  }
	} else {
	  for (int i = 0; i < ts.size(); i++) {
		temp.add_Turnable(ts.get(i).mirror(size));
	  }
	}
	turns.push_back(temp);
  }
  total_size += ts.size();
}

SimpleTurn TurnSequences::get(int i) const {
  int total_size = 0;
  for (size_t j=0; j<this->turns.size(); j++) {
    int prev = total_size;
    total_size += turns.at(j).size();
    if (total_size > i) {
      return turns.at(j).get(i-prev);
    }
  }
  throw std::invalid_argument("size out of scope");
}
