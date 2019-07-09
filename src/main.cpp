#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include "square.h"

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
  vector<vector<Square>> squares;
  Square x;
  x.set_a("\u001b[0m");
  x.set_c('X');
  for (int i=0; i<10; i++) {
    vector<Square> temp;
    for (int j=0; j<10; j++) {
      Square square {x};
      temp.push_back(square);
    }
    squares.push_back(temp);
  }

  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      string temp = squares.at(i).at(j).get_b();
      squares.at(i).at(j).set_b(temp+"\u001b[43m");
      temp = squares.at(9-j).at(9-i).get_b();
      squares.at(9-j).at(9-i).set_b(temp+"\u001b[36;1m");
      print(squares);
      sleep(100);
      clear(10);
    }
  }
  return 0;
}
