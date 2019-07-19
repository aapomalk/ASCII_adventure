
#include <memory>
#include "TurnSequence.h"
#include "TurnSequences.h"
#include <stdexcept>

SimpleTurn TurnSequences::get(int i) const {
  int total_size = 0;
  for (size_t j=0; j<this->turns.size(); j++) {
    int prev = total_size;
    total_size += turns.at(j)->size();
    if (total_size > i) {
      return turns.at(j)->get(i-prev);
    }
  }
  throw std::invalid_argument("size out of scope");
}
