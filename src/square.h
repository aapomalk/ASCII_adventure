
#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <string>

using std::string;

class Square {
 protected:
  char c;
  string before; // the ansi escapes
  string after; // return to normal

 public:
  Square(char c = ' ', string before = "", string after = "\u001b[0m");
  void set_c(char c);
  void set_b(string b);
  string get_b() const;
  void set_a(string a);
  void print() const;
};

#endif
