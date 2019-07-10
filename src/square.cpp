#include <iostream>
#include <string>
#include "square.h"

using std::string;
using std::cout;

Square::Square(char c, string before, string after)
  : c{c}, before{before}, after{after} {
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
