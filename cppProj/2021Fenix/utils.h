/* reminder : no using namespace
*/
#pragma once
#include <iostream>
#include <cassert>

typedef uint8_t RowId;
typedef uint8_t ColId; 
/* 
1 means lowest location on the board.
0 means outside the lowest location.
*/

typedef std::pair<RowId, ColId> Cell;
typedef std::pair<RowId, ColId> Step; // two values must consist of a zero and a one.

struct Mirror{ 
  Cell const cell;
  uint8_t ttl; //time to live in terms of remaining hits 
};
bool isSqrt2(float){
  return 1.414 < float && float < 1.415
}

class Photon{ // the photon's direction and current position
  Cell cur;
  Step next;
  float distanceTo(Mirror const & m) const{
    return 1;
  }
  char advance(){
    //this->cur to be updated
  }
  char move(std::list<Mirror> survivingMirrors){
    // what if the collection is empty?
    
    // handle the edge scenarios
    
    // if one distance is 1, then break; otherwise collect those mirrors at distance 1.42 and pass them as a collection
    list<Mirror> diagonalMirrors;
    for (auto const& aMirror: survivingMirrors){
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
