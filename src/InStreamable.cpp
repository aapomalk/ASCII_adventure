
#include "InStreamable.h"
#include <iostream>

std::istream& operator>> (std::istream& in, InStreamable &inAble) {
  inAble.streamIn(in);
  return in;
}
