/*
showcase layers of self-documenting typedef's, in the c++ library tradition

This class doesn't need Photon.h, Grid.h 
*/
#pragma once
#include "dumper.h" // needed for dumping pair<>
#include <cmath>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cctype>

typedef uint16_t Coordinate_t; // grid dimension won't exceed 16-bit int
typedef Coordinate_t RowId;
typedef Coordinate_t ColId; 
/* For both of the above,
1 means an edge location on the grid.
0 means outside the grid.
*/

typedef std::pair<RowId, ColId> Cell;
typedef std::pair<int, int> Step; // One of the two values must be a zero; ther other a +/-1.

struct Mirror{ 
  Cell const cell;
  int ttl; //time to live in terms of remaining hits. negative means forever.
  friend std::ostream & operator<<(std::ostream & os, Mirror const & c){
    os<<"["<<c.cell<<"]ttl="<<c.ttl; return os;
  }
};

typedef std::list<Mirror>::iterator MirrorIterator;

bool isSqrt2(float f){  return 1.4142 < f && f < 1.4143; }

float distance(Cell const & cellP, Cell const & cellQ){ //check2
    float aa = cellP.first - cellQ.first;
    float bb = cellP.second - cellQ.second;
    float ret = sqrt(aa*aa + bb*bb); 
    return ret;
}
Coordinate_t minXY(Cell const & _cur) {
    return std::min(_cur.first, _cur.second);
}
Coordinate_t maxXY(Cell const & _cur) {
    return std::max(_cur.first, _cur.second);
}