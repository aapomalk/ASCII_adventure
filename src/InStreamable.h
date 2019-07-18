
#ifndef _IN_STREAMABLE_H_
#define _IN_STREAMABLE_H_

#include <iostream>

class InStreamable {
  friend std::istream& operator>> (std::istream &in, InStreamable &inAble);
 public:
  virtual std::istream& streamIn(std::istream &) = 0; 
};

#endif
