
#include "Find.h"

// position find(const Rubic &cube, Side color, int xd = 1, int yd = 1);
// position find(const Rubic &cube, Side color1, Side color2, int zd = 1);
// position find(const Rubic &cube, Side color1, Side color2, Side color3);

Side find_any(const Rubic &cube, Side color) {
  for (int i=0; i<num_of_sides; i++) {
    Side current = static_cast<Side>(i);
    for (int j=0; j<cube.get_size(); j++) {
      for (int k=0; k<cube.get_size(); k++) {
	if (cube.piece(current, k, j) == color) {
	  return current;
	}
      }
    }
  }
  throw 0; // this should never be reached
}

// bool square_of_one_color(const Rubic &cube, Side color, int d, Side side = S1);

// bool side_of_one_color(const Rubic &cube, Side color);

// bool layer_finished(const Rubic &cube, int layer, Axis axis = A1);

// bool side_finished(const Rubic &cube, Side color);

// bool cube_finished(const Rubic &cube);
