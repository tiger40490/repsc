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
bool isSqrt2(float f){
  return 1.414 < f && f < 1.415;
}

struct Photon{ // the photon's direction and current position
  Cell cur;
  Step next;
  friend std::ostream & operator<<(std::ostream & os, Photon const & c){
    os<<"["<<c.cur<<"],<"<<c.next<<">"; return os;
  }
  float distanceTo(Mirror const & m) const{
    float aa = m.cell.first - cur.first;
    float bb = m.cell.second - cur.second;
    float ret = sqrt(aa*aa + bb*bb);
    return ret;
  }
  char advance(){
    //this->cur to be updated
    return 0;
  }
  char directHit(Mirror & m){ 
    ss<<"directHit \n";
    return 0;
  }
  char indirectHit(std::list<Mirror> & li){ 
    ss<<"INdirectHit \n";
    return 0;
  }

  char move(std::list<Mirror> & survivingMirrors){
    // what if the collection is empty?
    
    // handle the edge scenarios
    
    // if one distance is 1, then break; otherwise collect those mirrors at distance 1.42 and pass them as a collection
    std::list<Mirror> diagonalMirrors;
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
