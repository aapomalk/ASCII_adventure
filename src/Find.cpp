
#include "Find.h"
#include <iostream>

using std::cerr;

std::ostream& operator<<(std::ostream &os, const position &rhs) {
  os << rhs.side << " " << rhs.x << " " << rhs.y;
  return os;
}

position find(const Rubic &cube, Side color, int xd, int yd) {
  std::array<int, 4> xs {xd, yd, cube.get_size()-1-xd, cube.get_size()-1-yd};
  std::array<int, 4> ys {yd, cube.get_size()-1-xd, cube.get_size()-1-yd, xd};
  for (int x_ix = 0; x_ix < 4; x_ix++) {
    int x = xs.at(x_ix);
    int y = ys.at(x_ix);
    for (int i=0; i<num_of_sides; i++) {
      Side current = static_cast<Side>(i);
      if (cube.piece(current, x, y) == color) {
	return {current, x, y};
      }
    }
  }
  cerr << "position find(const Rubic &cube, Side color, int xd, int yd)";
  throw 0; // this should never be reached
}

position second(const Rubic &cube, Side current, int x_ix, int zd) {
  Side other;
  if (current == S1) {
    switch (x_ix) {
    case 0: other = S2; break;
    case 1: other = S3; break;
    case 2: other = S4; break;
    case 3: other = S5; break;
    default:
      cerr << "first of second";
      throw 0;
    }
    return {other, zd, 0};
  } else if (current == S2) {
    switch (x_ix) {
    case 0: return {S5, cube.get_size()-1, zd};
    case 1: return {S6, 0, cube.get_size()-1-zd};
    case 2: return {S3, 0, cube.get_size()-1-zd};
    case 3: return {S1, 0, cube.get_size()-1-zd};
    default:
      cerr << "second of second";
      throw 0;
    }
  } else if (current == S3) {
    switch (x_ix) {
    case 0: return {S2, cube.get_size()-1, zd};
    case 1: return {S6, zd, 0};
    case 2: return {S4, 0, cube.get_size()-1-zd};
    case 3: return {S1, cube.get_size()-1-zd, cube.get_size()-1};
    default:
      cerr << "third of second";
      throw 0;
    }
  } else if (current == S4) {
    switch (x_ix) {
    case 0: return {S3, cube.get_size()-1, zd};
    case 1: return {S6, cube.get_size()-1, zd};
    case 2: return {S5, 0, cube.get_size()-1-zd};
    case 3: return {S1, cube.get_size()-1, zd};
    default:
      cerr << "fourth of second";
      throw 0;
    }
  } else if (current == S5) {
    switch (x_ix) {
    case 0: return {S4, cube.get_size()-1, zd};
    case 1: return {S6, cube.get_size()-1-zd, cube.get_size()-1};
    case 2: return {S2, 0, cube.get_size()-1-zd};
    case 3: return {S1, zd, 0};
    default:
      cerr << "fifth of second";
      throw 0;
    }
  } else {
    switch (x_ix) {
    case 0: other = S2; break;
    case 1: other = S5; break;
    case 2: other = S4; break;
    case 3: other = S3; break;
    default:
      cerr << "sixth of second";
      throw 0;
    }
    return {other, cube.get_size()-1-zd, cube.get_size()-1};
  }
}

position find(const Rubic &cube, Side color1, Side color2, int zd) {
  std::array<int, 4> xs {0, zd, cube.get_size()-1, cube.get_size()-1-zd};
  std::array<int, 4> ys {zd, cube.get_size()-1, cube.get_size()-1-zd, 0};
  for (int x_ix = 0; x_ix < 4; x_ix++) {
    int x = xs.at(x_ix);
    int y = ys.at(x_ix);
    for (int i=0; i<num_of_sides; i++) {
      Side current = static_cast<Side>(i);
      if (cube.piece(current, x, y) == color1) {
        position pos2 = second(cube, current, x_ix, zd);
	if (cube.piece(pos2.side, pos2.x, pos2.y) == color2) {
	  return {current, x, y};
	}
      }
    }
  }
  cerr << "position find(const Rubic &cube, Side color1, Side color2, int zd)";
  throw 0; // this should never be reached
}

position find(const Rubic &cube, Side color1, Side color2, Side color3) {
  std::array<int, 4> xs {0, 0, cube.get_size()-1, cube.get_size()-1};
  std::array<int, 4> ys {0, cube.get_size()-1, cube.get_size()-1, 0};
  for (int x_ix = 0; x_ix < 4; x_ix++) {
    int x = xs.at(x_ix);
    int y = ys.at(x_ix);
    for (int i=0; i<num_of_sides; i++) {
      Side current = static_cast<Side>(i);
      if (cube.piece(current, x, y) == color1) {
        position pos2 = second(cube, current, x_ix, 0);
	position pos3 = second(cube, current, (x_ix+3)%4, cube.get_size()-1);
	if (cube.piece(pos2.side, pos2.x, pos2.y) == color2 &&
	    cube.piece(pos3.side, pos3.x, pos3.y) == color3) {
	  return {current, x, y};
	}
      }
    }
  }
  cerr << "position find(const Rubic &cube, Side color1, Side color2, Side color3)";
  throw 0; // this should never be reached
}

Side find_any(const Rubic &cube, Side color) {
  for (int j=0; j<cube.get_size(); j++) {
    for (int k=0; k<cube.get_size(); k++) {
      for (int i=0; i<num_of_sides; i++) {
	Side current = static_cast<Side>(i);
	if (cube.piece(current, k, j) == color) {
	  return current;
	}
      }
    }
  }
  cerr << "Side find_any(const Rubic &cube, Side color)";
  throw 0; // this should never be reached
}

bool square_of_one_color(const Rubic &cube, Side color, int d, Side side) {
  for (int i=0; i<4; i++) {
    for (int j=0; j<cube.get_size()-2*d-1; j++) {
      int x,y;
      switch (i) {
      case 0:
	x = d;
	y = d+j;
	break;
      case 1:
	x = d+j;
	y = cube.get_size()-1-d;
	break;
      case 2:
	x = cube.get_size()-1-d;
	y = cube.get_size()-1-d-j;
	break;
      case 3:
	x = cube.get_size()-1-d-j;
	y = d;
	break;
      default:
	cerr << "bool square_of_one_color(const Rubic &cube, Side color, int d, Side side)";
	throw 0;
      }
      for (int k=0; k<num_of_sides; k++) {
	Side current = static_cast<Side>(k);
	if (cube.piece(current, x, y) != color) {
	  return false;
	}
      }
    }
  }
  return true;
}

bool side_of_one_color(const Rubic &cube, Side color) {
  Side side = find_any(cube, color);
  for (int x=0; x<cube.get_size(); x++) {
    for (int y=0; y<cube.get_size(); y++) {
      if (cube.piece(side, x, y) != color) {
	return false;
      }
    }
  }
  return true;
}

bool layer_finished(const Rubic &cube, int layer, Axis axis) {
  for (Side side : cube.sides_in_axis.at(axis)) {
    Side color;
    for (int i=0; i<cube.get_size(); i++) {
      int x,y;
      if (axis == A1) {
	y = layer;
	x = i;
      } else if (axis == A2) {
	x = layer;
	y = i;
      } else {
	switch (side) {
	case S2:
	  x = cube.get_size()-1-layer;
	  y = i;
	  break;
	case S1:
	  y = cube.get_size()-1-layer;
	  x = i;
	case S4:
	  x = layer;
	  y = i;
	case S6:
	  y = layer;
	  x = i;
	default:
	  cerr << "bool layer_finished(const Rubic &cube, int layer, Axis axis)";
	  throw 0;
	}
      }
      if (i == 0) {
	color = cube.piece(side, x, y);
      } else if (cube.piece(side, x, y) != color) {
	return false;
      }
    }
  }
  return true;
}

bool side_finished(const Rubic &cube, Side color) {
  if (!side_of_one_color(cube, color)) {
    return false;
  }
  Side side = find_any(cube, color);
  int layer;
  switch (side) {
  case S1:
  case S2:
  case S3:
    layer = 0;
    break;
  default:
    layer = cube.get_size()-1;
  }
  Axis a;
  switch (side) {
  case S1:
  case S6:
    a = A1;
    break;
  case S2:
  case S4:
    a = A2;
    break;
  default:
    a = A3;
  }
  return layer_finished(cube, layer, a);
}

bool cube_finished(const Rubic &cube) {
  for (int k=0; k<num_of_sides; k++) {
    Side current = static_cast<Side>(k);
    if (!side_of_one_color(cube, current)) {
      return false;
    }
  }
  return true;
}
