/* 
*/
#pragma once
#include "dumper.h" // needed for dumping pair<>
//#include <list>
#include <cmath>
#include <iostream>
#include <cassert>

typedef uint16_t RowId;
typedef uint16_t ColId; 
/* For both of the above,
1 means lowest location on the board.
0 means outside the lowest location.
*/

typedef std::pair<RowId, ColId> Cell;
typedef std::pair<RowId, ColId> Step; // One of the two values must be a zero; ther other a one.

struct Mirror{ 
  Cell const cell;
  int ttl; //time to live in terms of remaining hits. negative means forever.
  friend std::ostream & operator<<(std::ostream & os, Mirror const & c){
    os<<"["<<c.cell<<"]ttl="<<c.ttl; return os;
  }
};
bool isSqrt2(float f){  return 1.4142 < f && f < 1.4143; }

float distance(Cell const & cellP, Cell const & cellQ){ //check2
    float aa = cellP.first - cellQ.first;
    float bb = cellP.second - cellQ.second;
    float ret = sqrt(aa*aa + bb*bb); 
    return ret;
}
