#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>
#include <time.h>
#include "square.h"
#include "screen.h"
#include "AsciiOutput.h"
#include "Rubic.h"
#include "TurnSequence.h"
#include <memory>

using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::flush;
using std::string;

void sleep(int amount) {
  std::chrono::milliseconds timespan(amount);
  std::this_thread::sleep_for(timespan);
}

void animate(const Turnable &turns, Rubic &cube, AsciiOutput &output, int t,
	     bool reverse, bool mirror) {
  if (reverse) {
    for (int i=turns.size(); i>0; i--) {
      SimpleTurn turn = turns.get(i-1);
      if (reverse) turn = turn.reverse();
      if (mirror) turn = turn.mirror(cube.get_size());
      cube.turn(turn);
      cube.update();
      sleep(t);
      output.clear();
      output.print();
    }
    return;
  }
  for (int i=0; i<turns.size(); i++) {
    SimpleTurn turn = turns.get(i);
    if (reverse) turn = turn.reverse();
    if (mirror) turn = turn.mirror(cube.get_size());
    cube.turn(turn);
    cube.update();
    sleep(t);
    output.clear();
    output.print();
  }
}

void clear(int lines) {
  for (int i=0; i<lines; i++) {
    cout << "\33[2K\r" << "\33[1A" << "\33[2K\r" << flush;
  }
}

vector<SimpleTurn> get_turns() {
  int number {0};
  cin >> number;
  vector<SimpleTurn> ret;
  for (int i = 0; i<number; i++) {
    SimpleTurn temp {A1, T1};
    cin >> temp;
    ret.push_back(temp);
  }
  return ret;
}

vector<SimpleTurn> get_shuffle(Rubic cube) {
  int number {0};
  cin >> number;
  vector<SimpleTurn> ret;
  for (int i=0; i<number; i++) {
    int position = rand() % cube.get_size();
    SimpleTurn temp {static_cast<Axis>(rand() % 3),
	static_cast<Amount>(rand() % 3), position, position};
    ret.push_back(temp);
  }
  return ret;
}

vector<int> get_arr() {
  vector<int> ret;
  for (int i=0; i<6; i++) {
    int temp;
    cin >> temp;
    ret.push_back(temp);
  }
  return ret;
}

int main(int argc, char **argv) {
  std::map<string, TurnSequence> memory;
  srand(time(NULL));
  int sleep_text = 500;
  int sleep_turn = 100;

  int size = 4;
  if (argc > 1) {
    size = atoi(argv[1]);
  }
  
  Screen squares {size*4+3, size*3+2, Square()};
  AsciiOutput &output {squares};

  Rubic cube {squares, size};

  cube.update();
  output.print();

  std::streambuf *cinbuf = cin.rdbuf();
  bool file = false;
  int file_command_id = 0;
  std::ifstream in;
 
  while (true) {
    bool mirror = false;
    bool reverse = false;
    TurnVector vec;    
    bool referencing = false;
    Turnable *temp = &vec;

    TurnSequence seq;
    if (file) {
      cout << file_command_id++;
    }
    cout << " > ";
    string command;
    cin >> command;
    cout << command << flush;
    if (file) {
      cout << endl;
    }
    if (command == "turn") {
      temp = &vec;
      vec.turns = get_turns();
      referencing = true;
    } else if (command == "new_sequence") {
      string name;
      cin >> name;
      if (name == "reverse" || name == "mirror") {
	cout << "reserved name" << endl;
      } else {
	seq.add_Turnables(get_turns());
	memory[name] = seq;
      }
    } else if (command == "sequence") {
      string name;
      cin >> name;
      if (name == "reverse") {
	reverse = true;
	cin >> name;
      }
      if (name == "mirror") {
	mirror = true;
	cin >> name;
      }
      temp = &(memory[name]);
      referencing = true;
    } else if (command == "edit_sequence") {
      string name;
      cin >> name;
      memory[name].set_arr(get_arr());
    } else if (command == "shuffle") {
      vec.turns = get_shuffle(cube);
      temp = &vec;
      referencing = true;
    } else if (command == "read_file") {
      file_command_id = 0;
      string name;
      cin >> name;
      if (in.is_open()) {
	in.close();
      }
      in = {std::ifstream(name.c_str())};
      cin.rdbuf(in.rdbuf());
      if (!in.is_open()) {
	cout << "couldn't open file " << name << endl;
      } else {
	file = true;
      }
    } else if (command == "end_file" || !cin.good()) {
      in.close();
      cin.rdbuf(cinbuf);
      file = false;
    } else if (command == "sleep_text") {
      cin >> sleep_text;
    } else if (command == "sleep_turn") {
      cin >> sleep_turn;
    } else if (command == "exit") {
      cout << "exiting" << endl;
      break;
    } else {
      cout << " undefined command " << command << flush;
      if (file) {
	cout << endl;
      }
    }
    sleep(sleep_text);
    clear(1);
    if (referencing) {
      animate(*temp, cube, output, sleep_turn, reverse, mirror);
    }
  }
  return 0;
}
