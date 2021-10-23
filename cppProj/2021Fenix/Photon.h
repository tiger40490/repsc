/* 
*/
#pragma once
#include "Grid.h"
#include <list>
//#include <cmath>
//#include <iostream>
#include <cassert>

struct Photon{ 
  Cell cur;
  Step next;
  Grid & grid;
  friend std::ostream & operator<<(std::ostream & os, Photon const & c){
    static std::pair<int, int> const S = {1,0};
    static std::pair<int, int> const N = {-1,0};
    static std::pair<int, int> const E = {0,1};
    static std::pair<int, int> const W = {0,-1};
    os<<"["<<c.cur<<"], <"<<c.next<<">"; 
    if (c.next == S) os<<"South";
    if (c.next == N) os<<"North";
    if (c.next == E) os<<"East";
    if (c.next == W) os<<"West";
    return os;
  }
  float distanceTo(Mirror const & m) const{ //check2
    return distance(m.cell, this->cur);
  }
  Cell getTargetCell() const{ //check1 .. rename to target()
    Cell ret = this->cur;
    ret.first += this->next.first;
    ret.second+= this->next.second;
    //ss<<ret<<" returned from getTargetCell()\n";
    return ret;
  }
  char advance(){ // LG2: how to indicate exit
    this->cur = getTargetCell();
    return 0;
  }
  void reverse1step(){ //may exit the grid
    next.first  *= -1;
    next.second *= -1;
    this->cur = getTargetCell();
    ss<<*this<<" after reverse1step()\n";
  }
  char directHit(MirrorIterator m){ 
    ss<<"directHit \n";
    //Cell const & originalTarget = this->getTargetCell();
    assert( getTargetCell() == m->cell );
    if (--m->ttl == 0){
      grid.del1mirror(m);
    }
    // need to adjust the photon to indicate Absorbed
    return 0;
  }
  char indirectHit(std::vector<MirrorIterator> const & vec){ 
    ss<<"indirectHit \n";
    Cell const & originalTarget = getTargetCell();
    for (auto const & aMirror: vec){
      assert(1==distance(aMirror->cell, originalTarget) && 
        "If no deflection, I would next land on a cell right next to Every mirror.");
    }
    
    auto & mirrorA = vec[0]->cell;
    if (vec.size() == 2){
      auto & mirrorB = vec[1]->cell;
      assert(2==distance(mirrorA, mirrorB));
      this->reverse1step();
    }else{
      assert(vec.size()==1);
          // todo: update this->next, based on mirrorA and originalTarget
      this->next = {originalTarget.first - mirrorA.first, 
                    originalTarget.second - mirrorA.second};
      this->cur = getTargetCell();
      ss<<*this<<" after deflection\n";
    } // Now check expired mirrors
    for (auto & aMirror: vec){
        if (--aMirror->ttl == 0) grid.del1mirror(aMirror);
    }    
	return 0;
  }

  char move1step(){
    // what if the collection is empty?
    
    // handle the edge scenarios
    
    // if one distance is 1, then break; otherwise collect those mirrors at distance 1.42 and pass them as a collection
    std::vector<MirrorIterator> diagonalMirrors;
    
    for(auto itr = grid.survivors.begin(); itr != grid.survivors.end(); ++itr) {
      float dist = distanceTo(*itr);
      if (dist == 1){
        // assert this->next would coincide with this mirror
        return this->directHit(itr);
      }
      if (isSqrt2(dist)){
        diagonalMirrors.push_back(itr);
      }
    }
    if (diagonalMirrors.size() == 0){ return advance(); }
    assert ( diagonalMirrors.size() < 3 && "3 or more diagonal mirrors ... are technically impossible" );
    return indirectHit(diagonalMirrors);
  }
};