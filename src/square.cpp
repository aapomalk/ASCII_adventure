#include <iostream>
#include <string>
#include "square.h"

using std::string;
using std::cout;

void Square::set_x(int x) {
  this->x = x;
}

void Square::set_y(int y) {
  this->y = y;
}

void Square::set_c(char c) {
  this->c = c;
}

void Square::set_b(string b) {
  this->before = b;
}

string Square::get_b() const {
  return this->before;
}

void Square::set_a(string a) {
  this->after = a;
}

void Square::print() const {
  cout << this->before << this->c << this->after;
}
