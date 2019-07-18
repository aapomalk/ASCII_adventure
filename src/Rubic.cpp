
#include "Rubic.h"
#include "screen.h"
#include <iostream>
#include <string>
#include <sstream>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::stoi;

std::istream& SimpleTurn::streamIn(std::istream &in) {
  int value {0};
  in >> value;
  Axis a = static_cast<Axis>(value);
  in >> value;
  Amount t = static_cast<Amount>(value);
  int p_start {0};
  in >> p_start;
  int p_end {p_start};
  in >> p_end;
  (*this) = {a, t, p_start, p_end};
  return in;
}

Amount mirror(Amount a) {
  switch (a) {
  case T1: return T3;
  case T2: return T2;
  case T3: return T1;
  default: return T1;
  }
}

Rubic::Rubic(Screen &screen, int size)
  : screen{screen},
	cube(6, vector<vector<Side>>(size, vector<Side>(size, S1))), copy{cube},
	size{size}, snake(size*4, vector<int>(3, 0)) {
	  int i=0;
	  for (auto &side : cube) {
		Side s = Side(i);
		for (auto &x : side) {
		  for (auto &square : x) {
			square = s;
		  }
		}
		i++;
	  }
	  copy = cube;
}

void Rubic::update() {
  int i = 0;
  for (const auto &side : cube) {
	int x = (this->size+1)*coordinates.at(i).at(0);
	int y = (this->size+1)*coordinates.at(i).at(1);
	int j = 0;
	for (const auto &inside : side) {
	  int k = 0;
	  for (const auto &s : inside) {
		Square& sq = this->screen.get_square(x+k, y+j);
		sq.set_b(colors.at(s));
		k++;
	  }
	  j++;
	}
	i++;
  }
}

void Rubic::single_turn(Axis a, Amount t, int position) {
  if (position < 0 || position >= this->size) {
    cout << position << endl;
    return;
  }
  if (position == 0) {
	switch (a) {
	case A1: turn_side_clockwise(S1, t); break;
	case A2: turn_side_clockwise(S2, t); break;
	case A3: turn_side_clockwise(S3, t); break;
	}
  } else if (position == this->size - 1) {
	switch (a) {
	case A1: turn_side_clockwise(S6, mirror(t)); break;
	case A2: turn_side_clockwise(S4, mirror(t)); break;
	case A3: turn_side_clockwise(S5, mirror(t)); break;
	}
  }
  // "normal" turn (not a whole side)
  const vector<Side> &order = sides_in_axis.at(a);
  int i=0;
  for (Side s : order) {
	int start_x,start_y,delta_x,delta_y;
	if (a == A1) {
	  start_x = this->size-1; delta_x = -1;
	  start_y = position; delta_y = 0;
	} else if (a == A2) {
	  delta_x = 0;
	  if (s == S1 || s == S3 || s == S6)  {
		start_x = position;
		start_y = 0; delta_y = 1;
	  } else {
		start_x = size - 1 - position;
		start_y = size - 1; delta_y = -1;
	  }
	} else { // a == A3
	  if (s == S1) {
		start_y = size - 1 - position; delta_y = 0;
		start_x = 0; delta_x = 1;
	  } else if (s == S4) {
		start_x = position; delta_x = 0;
		start_y = 0; delta_y = 1;
	  } else if (s == S6) {
		start_y = position; delta_y = 0;
		start_x = size - 1; delta_x = -1;
	  } else { // s == S2
		start_x = size - 1 - position; delta_x = 0;
		start_y = size - 1; delta_y = -1;
	  }
	}
	for (int j=0; j<size; j++) {
	  snake.at(i).at(0) = s;
	  snake.at(i).at(1) = start_x;
	  start_x += delta_x;
	  snake.at(i).at(2) = start_y;
	  start_y += delta_y;
	  i++;
	}
  }

  i=0;
  for (const auto &sn : snake) {
	int j = (i + size * (t+1)) % snake.size();
	const vector<int> &sn2 = snake.at(j);
	const Side copy = this->copy.at(sn.at(0)).at(sn.at(2)).at(sn.at(1));
	Side &orig = this->cube.at(sn2.at(0)).at(sn2.at(2)).at(sn2.at(1));
	orig = copy;
	i++;
  }
}

void Rubic::turn_side_clockwise(Side s, Amount t) {
  vector<vector<Side>> &side = cube.at(s);
  vector<vector<Side>> &copy = this->copy.at(s);
  int x = 0;
  for (const auto &c : copy) {
	int y = 0;
	for (const auto &s : c) {
	  int target_x;
	  int target_y;
	  switch (t) {
	  case T3:
		target_x = this->size - y - 1;
		target_y = x;
		break;
	  case T2:
		target_x = this->size - x - 1;
		target_y = this->size - y - 1;
		break;
	  case T1:
		target_x = y;
		target_y = this->size - x - 1;
	  }
	  side.at(target_x).at(target_y) = s;
	  y++;
	}
	x++;
  }
}

void Rubic::turn(const SimpleTurn &t) {
  for (int i=t.get_ps(); i<=t.get_pe(); i++) {
	this->single_turn(t.get_a(), t.get_t(), i);
  }
  copy = cube;
}
