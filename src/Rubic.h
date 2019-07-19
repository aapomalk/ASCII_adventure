
#ifndef _RUBIC_H_
#define _RUBIC_H_

#include <vector>
#include <string>
#include "screen.h"
#include "InStreamable.h"
#include <iostream>

using std::vector;
using std::string;

enum Side {S1,S2,S3,S4,S5,S6};
enum Amount {T1,T2,T3};
enum Axis {A1,A2,A3};
class SimpleTurn : public InStreamable {
  Axis a;
  Amount t;
  int p_start;
  int p_end;
 public:
 SimpleTurn(Axis a, Amount t, int p_start = 0, int p_end = 0)
   : a{a}, t{t}, p_start{p_start}, p_end{p_end} {}
  Axis get_a() const {return a;}
  Amount get_t() const {return t;}
  int get_ps() const {return p_start;}
  int get_pe() const {return p_end;}
  void set_ps(int i) {p_start = i;}
  void set_pe(int i) {p_end = i;}
  virtual std::istream& streamIn(std::istream &in) override;
  SimpleTurn mirror(int) const;
  SimpleTurn reverse() const;
};
Amount mirror_amount(Amount a);

class Rubic {
 private:
  const vector<string> colors {"\u001b[41m","\u001b[42m",
	  "\u001b[43m","\u001b[44m","\u001b[45m","\u001b[47m"};
  const vector<vector<int>> coordinates = {
	{1,0},{0,1},{1,1},{2,1},{3,1},{1,2}};
  const vector<vector<Side>> sides_in_axis = {
	{S2,S5,S4,S3},{S1,S3,S6,S5},{S1,S4,S6,S2}};
  Screen& screen;
  vector<vector<vector<Side>>> cube;
  vector<vector<vector<Side>>> copy;
  int size;
  vector<vector<int>> snake;

  void single_turn(Axis a, Amount t, int position);
  void turn_side_clockwise(Side s, Amount t);
  void move_to(Side s, Axis a, Amount t, int x, int y);
  
 public:
  Rubic(Screen& screen, int size);
 void update();
 void turn(const SimpleTurn &t);
 int get_size() {return size;}
};

#endif
