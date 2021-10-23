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

struct Photon{ // the photon's direction and current position
  Cell cur;
  Step next;
// ctor, assignment ... LGpp
  float distanceTo(Mirror const & m){
    return 1;
  }
  void check(std::list<Mirror> survivingMirrors){
    // what if the collection is empty?
    
    // if one distance is 1, then break; otherwise collect those mirrors at distance 1.42 and pass them as a collection
    for (auto const& i: survivingMirrors){
      float dist = distanceTo(i);
    }
  }
  void check3(Mirror m1, Mirror m2, Mirror m3){ // how to pass in the distances?
    // compute 3 distances. If one of them is 1m, then that's it.
    
  }
};


