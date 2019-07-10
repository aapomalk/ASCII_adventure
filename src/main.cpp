#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include "square.h"
#include "screen.h"

using std::vector;
using std::cout;
using std::endl;
using std::flush;
using std::string;

void sleep(int amount) {
  std::chrono::milliseconds timespan(amount);
  std::this_thread::sleep_for(timespan);
}

void clear(int lines) {
  for (int i=0; i<lines; i++) {
    cout << "\33[2K\r" << "\33[1A" << flush;
  }
}

void print(vector<vector<Square>> squares) {
  for (auto temp : squares) {
    for (auto sq : temp) {
      sq.print();
    }
    cout << endl;
  }
}

int main() {
  Screen squares {20, 10, Square('X')};

  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      squares.print();
      string temp = squares.get_square(i,j).get_b();
      squares.get_square(i,j).set_b(temp+"\u001b[43m");
      temp = squares.get_square(9-j,9-i).get_b();
      squares.get_square(9-j,9-i).set_b(temp+"\u001b[36;1m");
      sleep(100);
      squares.clear();
    }
  }
  return 0;
}
