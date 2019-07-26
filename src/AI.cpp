
#include "AI.h"
#include "Find.h"
#include <map>
#include <array>
#include <iostream>

// this is initially for cube of size 3
using std::map;
using std::cerr;
using std::array;

typedef bool (*fptr)(Rubic &cube, AsciiOutput &output, int sleep_time,
		     const map<string, TurnSequence> &memory,
		     const map<string, TurnSequences> &memory2);

bool no_turns(Rubic &cube, AsciiOutput &output, int sleep_time,
	      const map<string, TurnSequence> &memory,
	      const map<string, TurnSequences> &memory2) {
  return false;
}

bool turn_S1_up_S3_front(Rubic &cube, AsciiOutput &output, int sleep_time,
			 const map<string, TurnSequence> &memory,
			 const map<string, TurnSequences> &memory2) {
  position p1 = find(cube, S1);
  TurnVector turns;
  bool turned {false};
  switch (p1.side) {
  case S1:
    break;
  case S2:
    turns.turns.push_back({A3, T1, 0, 2});
    break;
  case S3:
    turns.turns.push_back({A2, T3, 0, 2});
    break;
  case S4:
    turns.turns.push_back({A3, T3, 0, 2});
    break;
  case S5:
    turns.turns.push_back({A2, T1, 0, 2});
    break;
  case S6:
    turns.turns.push_back({A2, T2, 0, 2});
    break;
  default:
    cerr << "switch case 1";
    throw 0;
  }
  if (turns.size() > 0) {
    turned = true;
    animate(turns, cube, output, sleep_time);
    turns.turns.clear();
  }
  position p3 = find(cube, S3);
  switch (p3.side) {
  case S2:
    turns.turns.push_back({A1, T3, 0, 2});
    break;
  case S3:
    break;
  case S4:
    turns.turns.push_back({A1, T1, 0, 2});
    break;
  case S5:
    turns.turns.push_back({A1, T2, 0, 2});
    break;
  default:
    cerr << "switch case 2";
    throw 0;
  }
  if (turns.size() > 0) {
    turned = true;
    animate(turns, cube, output, sleep_time);
  }
  return turned;
}

Amount turn_amount_cross(position current, position target) {
  if (current == target || current.side != target.side) {
    cerr << "can't turn amount";
    throw 0;
  }
  if (current.x == target.x || current.y == target.y) {
    return T2;
  }
  if ((current.x == 0 && target.y == 0) || (current.y == 0 && target.x == 2) ||
      (current.x == 2 && target.y == 2) || (current.y == 2 && target.x == 0)) {
    return T1;
  }
  return T3;
}

SimpleTurn upside_down_cross(position target) {
  if (target.x == 0) {
    return {A2, T2, 0, 0};
  }
  if (target.y == 2) {
    return {A3, T2, 0, 0};
  }
  if (target.x == 2) {
    return {A2, T2, 2, 2};
  }
  return {A3, T2, 2, 2};
}

bool put_cross_piece_in_place(Rubic &cube, AsciiOutput &output, int sleep_time,
			      position current, position target,
			      const map<string, TurnSequence> &memory){
  if (current == target) {
    return false;
  }
  TurnVector turns;
  if (current.side == S1) {
    SimpleTurn original_turn {A1, turn_amount_cross(current, target), 0, 0};
    turns.turns.push_back(original_turn);
    SimpleTurn upside_down {upside_down_cross(target)};
    turns.turns.push_back(upside_down);
    turns.turns.push_back(original_turn.reverse());
    turns.turns.push_back(upside_down.reverse());
  } else {
    if (current.side != S6) { // turn down and next time in place
      if (current.y == 2) {
	position side {S1, 0, 0};
	switch (current.side) {
	case S2:
	  side.x = 0;
	  side.y = 1;
	  break;
	case S3:
	  side.x = 1;
	  side.y = 2;
	  break;
	case S4:
	  side.x = 2;
	  side.y = 1;
	  break;
	case S5:
	  side.x = 1;
	  side.y = 0;
	  break;
	default:
	  cerr << "switch case 3";
	  throw 0;
	}
	if (side != target) {
	  turns.turns.push_back({A1, turn_amount_cross(side, target), 2, 2});
	}
	bool rewind {false};
	SimpleTurn forward {A1, T1};
	if (target != position{S1, 1, 2}) {
	  forward = {A1, turn_amount_cross(target, {S1, 1, 2}), 0, 2};
	  turns.turns.push_back(forward);
	  rewind = true;
	}
	if (memory.find("middle") == memory.end()) {
	  return false;
	}
	turns.addTurnable(memory.at("middle"));
	if (rewind) {
	  turns.turns.push_back(forward.reverse());
	}
      } else {
	Axis ax;
	if (current.side == S2 || current.side == S4) {
	  ax = A3;
	} else {
	  ax = A2;
	}
	Amount am;
	if (current.side == S2 || current.side == S5) {
	  am = T3;
	} else {
	  am = T1;
	}
	int pos;
	if (current.side == S3 || current.side == S4) {
	  pos = current.x;
	} else {
	  pos = cube.get_size()-1-current.x;
	}
	SimpleTurn turn_down {ax, am, pos, pos};
	turns.turns.push_back(turn_down);
	turns.turns.push_back({A1, T1, 2, 2});
	turns.turns.push_back(turn_down.reverse());
      }
    } else {
      position turned_target {S6, target.x,
	  (target.y == 1) ? target.y : ((target.y+2)%4)};
      if (current != turned_target) {
	turns.turns.push_back({A1,turn_amount_cross(current,turned_target),
	      2,2});
      }
      turns.turns.push_back(upside_down_cross(target));
    }
  }
  animate(turns, cube, output, sleep_time);
  return true;
}

bool make_cross(Rubic &cube, AsciiOutput &output, int sleep_time,
		const map<string, TurnSequence> &memory,
		const map<string, TurnSequences> &memory2) {
  bool turned {false};
  while (put_cross_piece_in_place(cube, output, sleep_time, find(cube, S1, S2),
				  {S1, 0, 1}, memory)) {
    turned = true;
  }
  while (put_cross_piece_in_place(cube, output, sleep_time, find(cube, S1, S3),
				  {S1, 1, 2}, memory)) {
    turned = true;
  }
  while (put_cross_piece_in_place(cube, output, sleep_time, find(cube, S1, S4),
				  {S1, 2, 1}, memory)) {
    turned = true;
  }
  while (put_cross_piece_in_place(cube, output, sleep_time, find(cube, S1, S5),
				  {S1, 1, 0}, memory)) {
    turned = true;
  }
  return turned;
}

bool put_corner_piece_in_place(Rubic &cube, AsciiOutput &output, int sleep_time,
			       const map<string, TurnSequence> &memory,
			       const map<string, TurnSequences> &memory2,
			       position current, position target) {
  if (current == target) {
    return false;
  }
  TurnVector turns;
  if (current.side == S1) {
    SimpleTurn st {A1, T1};
    if (current.x == 0 && current.y == 0) {
      st = {A3, T3, 2, 2};
    } else if (current.x == 0 && current.y == 2) {
      st = {A3, T3, 0, 0};
    } else if (current.x == 2 && current.y == 2) {
      st = {A3, T1, 0, 0};
    } else if (current.x == 2 && current.y == 0) {
      st = {A3, T1, 2, 2};
    } else {
      cerr << "if-else 1";
      throw 0;
    }
    turns.turns.push_back(st);
    turns.turns.push_back({A1, T1, 2, 2});
    turns.turns.push_back(st.reverse());
  } else if (current.side != S6 && current.y == 2) {
    if (current.side != S3) {
      turns.turns.push_back({A1, T1, 2, 2});
    } else {
      Side s = cube.piece(S6, current.x, 0);
      bool turn_top {true};
      SimpleTurn st {A1, T1};
      switch (s) {
      case S2:
	st = {A1, T3};
	break;
      case S3:
	turn_top = false;
	break;
      case S4:
	st = {A1, T1};
	break;
      case S5:
	st = {A1, T2};
	break;
      default:
	cerr << "switch-case 4";
	throw 0;
      }
      if (turn_top) {
	turns.turns.push_back(st);
      }
      if (memory.find("corner") == memory.end()) {
	return false;
      }
      if (current.x == 0) {
	turns.addTurnable(memory.at("corner"), true, false, cube.get_size());
      } else {
	turns.addTurnable(memory.at("corner"));
      }
      if (turn_top) {
	turns.turns.push_back(st.reverse());
      }
    }
  } else if (current.side != S6) {
    SimpleTurn st {A1, T1};
    if ((current.side == S2 && current.x == 0) ||
	(current.side == S5 && current.x == 2)) {
      st = {A3, T3, 2, 2};
    } else if ((current.side == S3 && current.x == 0) ||
	       (current.side == S2 && current.x == 2)) {
      st = {A3, T3, 0, 0};
    } else if ((current.side == S4 && current.x == 0) ||
	       (current.side == S3 && current.x == 2)) {
      st = {A3, T1, 0, 0};
    } else if ((current.side == S5 && current.x == 0) ||
	       (current.side == S4 && current.x == 2)) {
      st = {A3, T1, 2, 2};
    } else {
      cerr << "if-else 2";
      throw 0;
    }
    turns.turns.push_back(st);
    turns.turns.push_back({A1, T1, 2, 2});
    turns.turns.push_back(st.reverse());
  } else {
    position com {S6, 0, 0};
    if (current != com) {
      turns.turns.push_back({A1, T1, 2, 2});
    } else {
      if (memory.find("flip_corner") == memory.end()) {
	return false;
      }
      turns.addTurnable(memory.at("flip_corner"), true, false, cube.get_size());
    }
  }
  animate(turns, cube, output, sleep_time);
  return true;
}

bool place_corners(Rubic &cube, AsciiOutput &output, int sleep_time,
		   const map<string, TurnSequence> &memory,
		   const map<string, TurnSequences> &memory2) {
  bool turned {false};
  while (put_corner_piece_in_place(cube, output, sleep_time, memory, memory2,
				   find(cube, S1, S2, S5), {S1, 0, 0})) {
    turned = true;
  }
  while (put_corner_piece_in_place(cube, output, sleep_time, memory, memory2,
				   find(cube, S1, S3, S2), {S1, 0, 2})) {
    turned = true;
  }
  while (put_corner_piece_in_place(cube, output, sleep_time, memory, memory2,
				   find(cube, S1, S4, S3), {S1, 2, 2})) {
    turned = true;
  }
  while (put_corner_piece_in_place(cube, output, sleep_time, memory, memory2,
				   find(cube, S1, S5, S4), {S1, 2, 0})) {
    turned = true;
  }
  return turned;
}

bool put_layer2_piece_in_place(Rubic &cube, AsciiOutput &output, int sleep_time,
			       const map<string, TurnSequence> &memory,
			       const map<string, TurnSequences> &memory2,
			       Side color1, Side color2) {
  position current {find(cube, color1, color2)};
  position middle {find(cube, color1)};
  if (current.side == middle.side && current.x == 2) {
    return false;
  }
  TurnVector turns;
  if (current.side == S6) {
    current = find(cube, color2, color1);
    middle = find(cube, color2);
    Side temp = color1;
    color1 = color2;
    color2 = temp;
  }
  if (current.side != S3) {
    turns.turns.push_back({A1, T1, 0, 2});
  } else {
    if (memory.find("layer2") == memory.end()) {
      return false;
    }
    if (current.x == 2) {
      turns.addTurnable(memory.at("layer2"), false, true);
    } else if (current.x == 0) {
      turns.addTurnable(memory.at("layer2"), true, true, cube.get_size());
    } else {
      if (find(cube, color2).side == S4 && find(cube, color1).side == S3) {
	turns.addTurnable(memory.at("layer2"));
      } else if (find(cube,color2).side == S2 && find(cube,color1).side == S3) {
	turns.addTurnable(memory.at("layer2"), true, false, cube.get_size());
      } else {
	turns.turns.push_back({A1, T1, 0, 1});
      }
    }
  }
  animate(turns, cube, output, sleep_time);
  return true;
}

bool layer2(Rubic &cube, AsciiOutput &output, int sleep_time,
	    const map<string, TurnSequence> &memory,
	    const map<string, TurnSequences> &memory2) {
  bool turned {false};
  while (put_layer2_piece_in_place(cube, output, sleep_time, memory, memory2,
				   S2, S3)) {
    turned = true;
  }
  while (put_layer2_piece_in_place(cube, output, sleep_time, memory, memory2,
				   S3, S4)) {
    turned = true;
  }
  while (put_layer2_piece_in_place(cube, output, sleep_time, memory, memory2,
				   S4, S5)) {
    turned = true;
  }
  while (put_layer2_piece_in_place(cube, output, sleep_time, memory, memory2,
				   S5, S2)) {
    turned = true;
  }
  return turned;
}

bool upside_down(Rubic &cube, AsciiOutput &output, int sleep_time,
		 const map<string, TurnSequence> &memory,
		 const map<string, TurnSequences> &memory2) {
  TurnVector turns;
  turns.turns.push_back({A2, T2, 0, 2});
  animate(turns, cube, output, sleep_time);
  return true;
}

bool turn_cube(Rubic &cube, AsciiOutput &output, int sleep_time,
	       const map<string, TurnSequence> &memory,
	       const map<string, TurnSequences> &memory2) {
  TurnVector turns;
  turns.turns.push_back({A1, T1, 0, 2});
  animate(turns, cube, output, sleep_time);
  return true;
}

bool layer3_corners1_2(Rubic &cube, AsciiOutput &output, int sleep_time,
		       const map<string, TurnSequence> &memory,
		       const map<string, TurnSequences> &memory2) {
  if (memory2.find("corners") == memory2.end()) {
    return false;
  }
  animate(memory2.at("corners"), cube, output, sleep_time);
  return true;
}

bool layer3_corners1_1(Rubic &cube, AsciiOutput &output, int sleep_time,
		       const map<string, TurnSequence> &memory,
		       const map<string, TurnSequences> &memory2) {
  turn_cube(cube, output, sleep_time, memory, memory2);
  return layer3_corners1_2(cube, output, sleep_time, memory, memory2);
}

typedef bool (*case_ptr)(const Rubic &cube);

bool basic_final(const Rubic &cube) {
  return (cube.piece(S1, 0, 2) == S6 && cube.piece(S1, 2, 2) == S6 &&
	  cube.piece(S5, 2, 0) == S6 && cube.piece(S5, 0, 0) == S6 &&
	  cube.piece(S3, 0, 0) != cube.piece(S3, 2, 0));
}
bool basic_sideways(const Rubic &cube) {
  return (cube.piece(S3, 0, 0) == S6 && cube.piece(S4, 0, 0) == S6 &&
	  cube.piece(S4, 2, 0) == S6 && cube.piece(S5, 2, 0) == S6);
}
bool basic_1up(const Rubic &cube) {
  return (cube.piece(S3, 0, 0) == S6 && cube.piece(S1, 2, 2) == S6 &&
	  cube.piece(S5, 0, 0) == S6 && cube.piece(S2, 0, 0) == S6);
}
bool basic_1up2(const Rubic &cube) {
  return (cube.piece(S3, 2, 0) == S6 && cube.piece(S1, 0, 2) == S6 &&
	  cube.piece(S5, 2, 0) == S6 && cube.piece(S4, 2, 0) == S6);
}
bool basic_r(Rubic &cube, AsciiOutput &output, int sleep_time,
		   const map<string, TurnSequence> &memory,
		   const map<string, TurnSequences> &memory2) {
  if (memory.find("basic") == memory.end()) {
    return false;
  }
  animate(memory.at("basic"), cube, output, sleep_time);
  return true;
}

bool basic_reverse(const Rubic &cube) {
  return (cube.piece(S1, 0, 2) == S6 && cube.piece(S1, 2, 2) == S6 &&
	  cube.piece(S5, 2, 0) == S6 && cube.piece(S5, 0, 0) == S6 &&
	  cube.piece(S3, 0, 0) == cube.piece(S3, 2, 0));
}
bool basic_reverse_r(Rubic &cube, AsciiOutput &output, int sleep_time,
		     const map<string, TurnSequence> &memory,
		     const map<string, TurnSequences> &memory2) {
  if (memory.find("basic") == memory.end()) {
    return false;
  }
  animate(memory.at("basic"), cube, output, sleep_time, true); // reverse
  return true;
}

void fill_cases(map<case_ptr, fptr> &cNr) {
  cNr[basic_final] = basic_r;
  cNr[basic_reverse] = basic_reverse_r;
  cNr[basic_sideways] = basic_r;
  cNr[basic_1up] = basic_r;
}

bool layer3_corners2(Rubic &cube, AsciiOutput &output, int sleep_time,
		    const map<string, TurnSequence> &memory,
		    const map<string, TurnSequences> &memory2) {
  if (memory.find("basic") == memory.end()) {
    return false;
  }
  map<case_ptr, fptr> casesNreactions;
  fill_cases(casesNreactions);
  // match to cases, if not found, turn the cube
  for (int i=0; i<3; i++) {
    for (const auto &one_case : casesNreactions) {
      if (one_case.first(cube)) {
	one_case.second(cube, output, sleep_time, memory, memory2);
	return true;
      }
    }
    turn_cube(cube, output, sleep_time, memory, memory2);
  }
  return false;
}

bool layer3_middles(Rubic &cube, AsciiOutput &output, int sleep_time,
		    const map<string, TurnSequence> &memory,
		    const map<string, TurnSequences> &memory2) {
  return false;
}

fptr figure_phase(Rubic &cube) {
  if (!side_finished(cube, S1)) {
    position p1 = find(cube, S1);
    position p3 = find(cube, S3);
    if (p1.side != S1 || p3.side != S3) {
      return turn_S1_up_S3_front;
    }
    position c2 = find(cube, S1, S2);
    position c3 = find(cube, S1, S3);
    position c4 = find(cube, S1, S4);
    position c5 = find(cube, S1, S5);
    if (c2.side != S1 || c3.side != S1 || c4.side != S1 || c5.side != S1 ||
	c2.x != 0 || c3.y != 2 || c4.x != 2 || c5.y != 0) {
      return make_cross;
    }
    position c32 = find(cube, S1, S3, S2);
    position c43 = find(cube, S1, S4, S3);
    position c54 = find(cube, S1, S5, S4);
    position c25 = find(cube, S1, S2, S5);
    if (c32.side != S1 || c32.x != 0 || c32.y != 2 ||
	c43.side != S1 || c43.x != 2 || c43.y != 2 ||
	c54.side != S1 || c54.x != 2 || c54.y != 0 ||
	c25.side != S1 || c25.x != 0 || c25.y != 0) {
      return place_corners;
    }
    return no_turns;
  } else {
    Side side = find_any(cube, S1);
    bool layer2_finished {false};
    if (side == S1 || side == S6) {
      layer2_finished = layer_finished(cube, 1);
    } else {
      return turn_S1_up_S3_front;
    }
    if (!layer2_finished) {
      return layer2;
    } else {
      if (side == S1) {
	return upside_down;
      } else {
	int i=0;
	array<Side, 3> a32 {S6, S2, S3};
	array<Side, 3> a54 {S6, S4, S5};
	position c32;
	do {
	  c32 = find(cube, a32.at(i%3), a32.at((i+1)%3), a32.at((i+2)%3));
	  i++;
	} while(c32.side != S1);
	
	if (c32.x != 0 || c32.y != 2) {
	  return turn_cube;
	}
	
	position c54;
	do {
	  c54 = find(cube, a54.at(i%3), a54.at((i+1)%3), a54.at((i+2)%3));
	  i++;
	} while(c54.side != S1);
	
	if (c54.x == 0) {
	  return layer3_corners1_1;
	} else if (c54.y == 2) {
	  return layer3_corners1_2;
	} else if (cube.piece(S1, 0, 0) != S6 || cube.piece(S1, 2, 0) != S6 ||
		   cube.piece(S1, 0, 2) != S6 || cube.piece(S1, 2, 2) != S6) {
	  return layer3_corners2;
	} else {
	  return layer3_middles;
	}
      }
    }
  }
  return no_turns;
}

void finish_phase(Rubic &cube, AsciiOutput &output, int sleep_time,
		  const map<string, TurnSequence> &memory,
		  const map<string, TurnSequences> &memory2) {
  fptr phase = figure_phase(cube);
  phase(cube, output, sleep_time, memory, memory2);
}

void finish(Rubic &cube, AsciiOutput &output, int sleep_time,
	    const map<string, TurnSequence> &memory,
	    const map<string, TurnSequences> &memory2) {
  while (!cube_finished(cube)) {
    fptr phase = figure_phase(cube);
    if (!phase(cube, output, sleep_time, memory, memory2)) {
      break;
    }
  }
}
