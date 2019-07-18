#include <iostream>
#include <vector>
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

// void clear(int lines) {
//   for (int i=0; i<lines; i++) {
//     cout << "\33[2K\r" << "\33[1A" << flush;
//   }
// }

// void print(vector<vector<Square>> squares) {
//   for (auto temp : squares) {
//     for (auto sq : temp) {
//       sq.print();
//     }
//     cout << endl;
//   }
// }

int main(int argc, char **argv) {
  srand(time(NULL));

  int size = 4;
  if (argc > 1) {
    size = atoi(argv[1]);
  }
  
  Screen squares {size*4+3, size*3+2, Square()};
  AsciiOutput &output {squares};

  Rubic cube {squares, size};

  cube.update();
  // int start = 0;
  // int end = 0;
  // for (int i=0; i<30; i++) {
  // 	output.print();
  // 	Axis a = Axis(rand() % 3);
  // 	Amount t = Amount(rand() % 3);
  // 	start = rand() % size;
  // 	end = start + (rand() % (size - start));
  // 	cube.turn(Turn{a, t, start, end});
  // 	cube.update();
  // 	sleep(100);
  // 	output.clear();
  // }

  TurnSequence basic {};
  vector<int> arr(6);
  arr.at(0) = arr.at(1) = arr.at(4) = arr.at(5) = 0;
  arr.at(2) = arr.at(3) = 2;
  basic.set_arr(arr);
  cout << "give 6 turns: ";
  SimpleTurn temp {A1, T1};
  for (int i=0; i<6; i++) {
    cin >> temp;
    basic.add_Turnable(temp);
  }
  

  for (int i=0; i<basic.size(); i++) {
    output.print();
    cube.turn(basic.get(i));
    cube.update();
    sleep(3000);
    output.clear();
  }
  output.print();
  // for (int i=0; i<10; i++) {
  //   for (int j=0; j<10; j++) {
  //     output.print();
  //     string temp = squares.get_square(i,j).get_b();
  //     squares.get_square(i,j).set_b(temp+"\u001b[43m");
  //     temp = squares.get_square(9-j,9-i).get_b();
  //     squares.get_square(9-j,9-i).set_b(temp+"\u001b[36;1m");
  //     sleep(100);
  //     output.clear();
  //   }
  // }
  return 0;
}
