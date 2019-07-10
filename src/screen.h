
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <vector>
#include "square.h"
#include "AsciiOutput.h"

using std::vector;

class Screen : public AsciiOutput {
 protected:
  int width;
  int height;
  vector<vector<Square>> screen;
  
 public:
  Screen(int width = 10, int height = 10, Square sq = {});
  int get_width();
  int get_height();
  Square& get_square(int x, int y);
  virtual void clear() const;
  virtual void print() const;
};

#endif
