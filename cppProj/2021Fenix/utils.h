/* 
*/
#pragma once
#include "dumper.h" // needed for dumping pair<>
#include <list>
#include <cmath>
#include <iostream>
#include <cassert>

typedef uint16_t RowId;
typedef uint16_t ColId; 
/* 
1 means lowest location on the board.
0 means outside the lowest location.
*/

typedef std::pair<RowId, ColId> Cell;
typedef std::pair<RowId, ColId> Step; // two values must consist of a zero and a one.

struct Mirror{ 
  Cell const cell;
  int ttl; //time to live in terms of remaining hits. negative means forever.
  friend std::ostream & operator<<(std::ostream & os, Mirror const & c){
    os<<"["<<c.cell<<"]ttl="<<c.ttl; return os;
  }
};
bool isSqrt2(float f){  return 1.414 < f && f < 1.415; }
float distance(Cell const & cellP, Cell const & cellQ){ //check2
    float aa = cellP.first - cellQ.first;
    float bb = cellP.second - cellQ.second;
    float ret = sqrt(aa*aa + bb*bb); 
    return ret;
}
struct Photon{ 
  Cell cur;
  Step next;
  friend std::ostream & operator<<(std::ostream & os, Photon const & c){
    os<<"["<<c.cur<<"],<"<<c.next<<">"; return os;
  }
  float distanceTo(Mirror const & m) const{ //check2
    return distance(m.cell, this->cur);
  }
  Cell getTargetCell() const{ //check1 .. rename to target()
    Cell ret = this->cur;
    ret.first += this->next.first;
    ret.second+= this->next.second;
    ss<<ret<<" returned from getTargetCell()\n";
    return ret;
  }
  char advance(){ // LG2: how to indicate leaving
    this->cur = getTargetCell();
    return 0;
  }
  char directHit(Mirror & m){ 
    ss<<"directHit \n";
    //Cell const & originalTarget = this->getTargetCell();
    assert( this->getTargetCell() == m.cell );
    // need to adjust the photon to indicate Absorbed
    return 0;
  }
  char indirectHit(std::vector<Mirror> & vec){ 
    ss<<"indirectHit \n";
    Cell const & originalTarget = this->getTargetCell();
    for (auto const & aMirror: vec){
      assert(1==distance(aMirror.cell, originalTarget));
    }
    return 0;
  }

  char move(std::list<Mirror> & survivingMirrors){
    // what if the collection is empty?
    
    // handle the edge scenarios
    
    // if one distance is 1, then break; otherwise collect those mirrors at distance 1.42 and pass them as a collection
    std::vector<Mirror> diagonalMirrors;
    for (auto& aMirror: survivingMirrors){
      float dist = distanceTo(aMirror);
      if (dist == 1){
        // assert this->next would coincide with this mirror
        return this->directHit(aMirror);
      }
      if (isSqrt2(dist)){
        diagonalMirrors.push_back(aMirror);
      }
    }
    if (diagonalMirrors.size() == 0){ return advance(); }
    assert ( diagonalMirrors.size() < 3);
    return indirectHit(diagonalMirrors);
  }
};
