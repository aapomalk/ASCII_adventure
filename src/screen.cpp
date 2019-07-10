
#include <vector>
#include <iostream>
#include "square.h"
#include "screen.h"

using std::vector;
using std::cout;
using std::endl;
using std::flush;

Screen::Screen(int width, int height, Square sq)
  : width{width}, height{height},
    screen(height, vector<Square>(width, sq)) {
 
 }
  
Square& Screen::get_square(int x, int y) {
  return this->screen.at(y).at(x);
}

void Screen::clear() const {
  for (int i=0; i<this->height; i++) {
    cout << "\33[2K\r" << "\33[1A";
  }
  cout << flush;
}

void Screen::print() const {
  for (const auto &temp : this->screen) {
    for (const auto &sq : temp) {
      sq.print();
    }
    cout << endl;
  }
}

