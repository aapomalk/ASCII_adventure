
#include "AI.h"
#include "Find.h"

// this is initially for cube of size 3

typedef bool (*fptr)(Rubic &cube, AsciiOutput &output, int sleep_time,
		     std::map<string, TurnSequence> memory,
		     std::map<string, TurnSequences> memory2);

bool turn_S1_up_S3_front(Rubic &cube, AsciiOutput &output, int sleep_time,
			 std::map<string, TurnSequence> memory,
			 std::map<string, TurnSequences> memory2) {
  return false;
}

bool make_cross(Rubic &cube, AsciiOutput &output, int sleep_time,
		std::map<string, TurnSequence> memory,
		std::map<string, TurnSequences> memory2) {
  return false;
}

bool sort_cross(Rubic &cube, AsciiOutput &output, int sleep_time,
		std::map<string, TurnSequence> memory,
		std::map<string, TurnSequences> memory2) {
  return false;
}

bool place_corners(Rubic &cube, AsciiOutput &output, int sleep_time,
		   std::map<string, TurnSequence> memory,
		   std::map<string, TurnSequences> memory2) {
  return false;
}

bool phase1(Rubic &cube, AsciiOutput &output, int sleep_time,
	    std::map<string, TurnSequence> memory,
	    std::map<string, TurnSequences> memory2) {
  if (memory.find("basic") != memory.end()) {
    animate(memory.at("basic"), cube, output, sleep_time);
    return true;
  }
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
    if (c2.side != S1 || c3.side != S1 || c4.side != S1 || c5.side != S1) {
      return make_cross;
    }
    if (c2.x != 0 || c3.y != 2 || c4.x != 2 || c5.y != 0) {
      return sort_cross;
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
    throw 0;
  } else {
    //Side pos = find_any(cube, S1);
  }
  return 0;
}

void finish_phase(Rubic &cube, AsciiOutput &output, int sleep_time,
		  std::map<string, TurnSequence> memory,
		  std::map<string, TurnSequences> memory2) {
  fptr phase = figure_phase(cube);
  phase(cube, output, sleep_time, memory, memory2);
}

void finish(Rubic &cube, AsciiOutput &output, int sleep_time,
	    std::map<string, TurnSequence> memory,
	    std::map<string, TurnSequences> memory2) {
  while (!cube_finished(cube)) {
    fptr phase = figure_phase(cube);
    if (!phase(cube, output, sleep_time, memory, memory2)) {
      break;
    }
  }
}
