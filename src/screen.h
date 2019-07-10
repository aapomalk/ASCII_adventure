
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <vector>
#include "square.h"

using std::vector;

class Screen {
 protected:
  int width;
  int height;
  vector<vector<Square>> screen;
  
 public:
  Screen(int width = 10, int height = 10, Square sq = {});
  Square& get_square(int x, int y);
  void clear() const;
  void print() const;
};

#endif
