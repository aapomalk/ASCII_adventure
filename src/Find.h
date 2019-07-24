
#ifndef _FIND_H_
#define _FIND_H_

#include "Rubic.h"

struct position {
  Side side;
  int x;
  int y;
};

// all of these return the position of the color/color1 for first match
// if xd and yd are both 0 -> corner piece
// limits of xd and yd are from 0 to size/2
position find(const Rubic &cube, Side color, int xd = 1, int yd = 1);
// if zd = 0 -> corner piece
position find(const Rubic &cube, Side color1, Side color2, int zd = 1);
// same as above with zd = 0 (assuming color combination is correct
position find(const Rubic &cube, Side color1, Side color2, Side color3);

// first match of the color
Side find_any(const Rubic &cube, Side color);

// on one side, if d = 0 only the outermost square is checked
// d = 1 the on step inside is checked
// limits of d are from 0 to size/2
bool square_of_one_color(const Rubic &cube, Side color, int d, Side side = S1);

// this checks where the colors are - if on same side -> true, else -> false
bool side_of_one_color(const Rubic &cube, Side color);

bool layer_finished(const Rubic &cube, int layer, Axis axis = A1);

// this combines the side_of_one_color and matching layer_finished calls
bool side_finished(const Rubic &cube, Side color);

// this checks if all sides are of one color
bool cube_finished(const Rubic &cube);

#endif
