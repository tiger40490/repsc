/* 
*/
#pragma once
#include "Grid.h"
#include <list>
#include <cassert>

struct Photon{ // should become a class if more time given
  Cell cur;
  Step next; //rename to nextStep?
  Grid & grid; //rename to theGrid?
  friend std::ostream & operator<<(std::ostream & os, Photon const & c){
    static std::pair<int, int> const S = {1,0};
    static std::pair<int, int> const N = {-1,0};
    static std::pair<int, int> const E = {0,1};
    static std::pair<int, int> const W = {0,-1};
    os<<"{"<<c.cur<<"}, <"<<c.next<<">"; 
    if (c.next == S) os<<"South";
    if (c.next == N) os<<"North";
    if (c.next == E) os<<"East";
    if (c.next == W) os<<"West";
    return os;
  }
  float distanceTo(Mirror const & m) const{ return distance(m.cell, cur);} //check3
  bool isLeaving() const{
    if (1 == cur.first  && next.first == -1) return true;
    if (1 == cur.second && next.second == -1) return true;
    if (grid.length == cur.first  && next.first == 1) return true;
    if (grid.length == cur.second && next.second == 1) return true;
    return false;
  }
  Cell getTargetCell() const{ //check1 .. rename to target()
    Cell ret = this->cur;
    ret.first += this->next.first;
    ret.second+= this->next.second;
    //ss<<ret<<" returned from getTargetCell()\n";
    return ret;
  }
  // ^^^^^^^^^ end of const member functions ^^^^^^^^^^
  /* chokepoint for all movements of phton
  return value not in use for now ... hard to propagate.
  */
  bool updateCurLocation(){  
    if (isLeaving()) {
      ss<<*this<<" is leaving, detected in updateCurLocation()\n";
      return false;
    }
    this->cur = getTargetCell();
    return true;
  }
  //char goStraight(){ return this->updateCurLocation();} // not in use
  void reverse1step(){ //needed by ScenarioE
    next.first  *= -1;
    next.second *= -1;
    this->updateCurLocation();
    ss<<*this<<" after reverse1step()\n";
  }
  char directHit(MirrorIterator m){ 
    ss<<"directHit on "<<*m<<std::endl;
    assert( getTargetCell() == m->cell && 
"by the rules, ONLY way to be 1-meter near a mirror is a direct hit!");
    if (--m->ttl == 0) grid.del1mirror(m);
    return 'a'; //absorbed
  }
  char indirectHit(std::vector<MirrorIterator> const & vec){ 
    ss<<"indirectHit \n";
    Cell const & originalTarget = getTargetCell();
    for (auto const & aMirror: vec){
      assert(1==distance(aMirror->cell, originalTarget) && 
        "If no deflection, I would next land on a cell right next to Every mirror passed to this function.");
    }
    
    auto & mirrorA = vec[0]->cell;
    if (vec.size() == 2){
      auto & mirrorB = vec[1]->cell;
      assert(2==distance(mirrorA, mirrorB) && "The two mirrors in Scenario Y should be 2-meter apart");
      this->reverse1step();
    }else{
      assert(vec.size()==1);
      this->next = {originalTarget.first  - mirrorA.first, 
                    originalTarget.second - mirrorA.second};
      this->updateCurLocation();
      ss<<*this<<" after deflection by Mirror at ["<< mirrorA<<"]\n";
    } // Now check expired mirrors
    for (auto & m: vec){
        if (--(m->ttl) == 0) grid.del1mirror(m);
    }    
	  return 0;
  }

  char move1step(){        
    // if any distance is 1m, then break; otherwise collect those mirrors at distance 1.42 and pass them as a collection
    std::vector<MirrorIterator> diagonalMirrors;
    for(auto itr = grid.survivors.begin(); itr != grid.survivors.end(); ++itr) {
      float dist = distanceTo(*itr);
      if (dist == 1) return directHit(itr); 
      if (isSqrt2(dist)) diagonalMirrors.push_back(itr); 
    }
    
    if (diagonalMirrors.size() == 0) return updateCurLocation(); // one step forward
    
    assert ( diagonalMirrors.size() < 3 && "3 or more diagonal mirrors ... are technically impossible" );
    return indirectHit( diagonalMirrors );
  }
  
  std::string roundTrip(){ // returns the exit cell name
  // todo handle initial edge senarios
    while(true){
      ss<<*this<<" <-- before move1step\n";
      char status = this->move1step(); 
      //if (status == ABSORBED) return "";
      if (isLeaving()){
        ss<<*this<<" <-- the last cell\n";
        return "{"+std::to_string(cur.first)
              +","+std::to_string(cur.second)+"}";
      }
    } // while
  } //function
};