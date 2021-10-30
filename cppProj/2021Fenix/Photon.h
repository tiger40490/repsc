/* 
*/
#pragma once
#include "Grid.h"
#include <list>
#include <stdexcept>
#include <cassert>

static char const ABSORBED = 'a';
static char const REVERSE = 'r';
    static std::pair<int, int> const S = {1,0};
    static std::pair<int, int> const N = {-1,0};
    static std::pair<int, int> const E = {0,1};
    static std::pair<int, int> const W = {0,-1};

class Photon{ 
  Cell _cur;
  Step _next; //
  Grid & _grid; // photons exist on a grid, but Grid class doesn't need a photon
  bool _isAtStart = true; 
  friend std::ostream & operator<<(std::ostream & os, Photon const & c){
    os<<"{"<<c._cur<<"}..<"<<c._next<<">"; 
    if (c._next == S) os<<"South";
    if (c._next == N) os<<"North";
    if (c._next == E) os<<"East";
    if (c._next == W) os<<"West";
    return os;
  }
  float distanceTo(Mirror const & m) const{ return distance(m.address, _cur);} //check3
  bool isLeaving(/*bool isStrict=true*/) const{
    //ss<<_isAtStart<<" = _isAtStart\n";
    if (!_isAtStart){
      if (1 > minXY(_cur) || maxXY(_cur) > _grid.length ) 
        throw std::runtime_error(
      "photon is NOT at the start but its current location is outside the grid. Programmer or data error");
    }
    if (1 == _cur.first  && _next.first == -1) return true; // going out to north
    if (1 == _cur.second && _next.second == -1) return true; // going out to west
    if (_grid.length == _cur.first  && _next.first == 1) return true; // going out to south
    if (_grid.length == _cur.second && _next.second == 1) return true; // going out to east
    return false;
  }
  Cell target() const{ //check3
    Cell ret = _cur;
    ret.first += _next.first;
    ret.second+= _next.second;
    //ss<<ret<<" returned from target()\n";
    return ret;
  }
  std::string checkEdgeMirrors() const{ // check ScenarioE
    Cell const & entryCell = this->target();
    assert( (minXY(entryCell)==1 || maxXY(entryCell)==_grid.length) 
      && "the first target cell of a ray must be on the edge");
    
    // collect any mirror 1.42 m away
    std::vector<MirrorIterator> diagonalMirrors;
    for(auto itr = _grid.survivors.begin(); itr != _grid.survivors.end(); ++itr) {
      float dist = distanceTo(*itr);
      if (dist == 1) return ""; // I prefer a single code path of move1step -> directHit
      if (isSqrt2(dist)) diagonalMirrors.push_back(itr); 
    }
    //ss<<diagonalMirrors.size()<<" = initial count of diagonalMirrors\n";
    if (diagonalMirrors.size() == 0) return "";
    
    for (auto & m: diagonalMirrors){
        if (--(m->ttl) == 0) _grid.del1mirror(m);
    }   
    _grid.leaveBreadcrumb(_cur, REVERSE);
    return "{"+std::to_string(entryCell.first)
          +","+std::to_string(entryCell.second)+"}";
  }
  char convertDirectiontoArrow() const{
    if (_next == S) return 'v';
    if (_next == N) return '^';
    if (_next == E) return '>';
    if (_next == W) return '<';
    assert(false && "should never reach here");
    return ' ';
  }
  //char 
  // ^^^^^^^^^ above are const member functions ^^^^^^^^^^
  // ^^^^^^^^^ below are movement operations ^^^^^^^^^^
  
  /* tryUpdateCurLocation() is the chokepoint for all movements of the photon !
  
  Note return value (true=updated) is not in use for now ... hard to propagate out.
  
  Note the design requires we check the photon isLeaving() only before updating its location , not after! 
  */
  bool tryUpdateCurLocation(char dirChange=0){  
    if (dirChange != 0)
      _grid.leaveBreadcrumb(_cur, dirChange);
    if (isLeaving()) {
      ss<<*this<<" is leaving the grid, detected at start of tryUpdateCurLocation()\n";
      return false;
    }

    //char prevDirection = convertDirectiontoArrow();
    _cur = target();
    char dir = convertDirectiontoArrow();
    // update dir
    
    
    _grid.leaveBreadcrumb(_cur, dir);
    _isAtStart = false;
    //ss<<*this<<"  <-- at end of tryUpdateCurLocation()\n";
    return true;
  }
  void reverse1step(){
    _next.first  *= -1;
    _next.second *= -1;
    this->tryUpdateCurLocation(REVERSE);
    ss<<*this<<" after tryUpdateCurLocation(), at end of reverse1step()\n";
  }
  char directHit (MirrorIterator m){ 
    ss<<"directHit on "<<*m<<std::endl;
    assert( target() == m->address && 
"by the rules, ONLY way to be 1-meter near a mirror is a direct hit!");
    if (--m->ttl == 0) _grid.del1mirror(m);
    return ABSORBED; //absorbed
  }
  char indirectHit(std::vector<MirrorIterator> const & vec){ 
    ss<<"indirectHit \n";
    Cell const & originalTarget = target();
    for (auto const & aMirror: vec){
      assert(1==distance(aMirror->address, originalTarget) && 
        "If no deflection, I would _next land on a cell right _next to Every mirror passed to this function.");
    }
    
    auto & mirrorA = vec[0]->address;
    if (vec.size() == 2){
      auto & mirrorB = vec[1]->address;
      assert(2==distance(mirrorA, mirrorB) && "The two mirrors in Scenario Y should be 2-meter apart");
      this->reverse1step();
    }else{
      assert(vec.size()==1);
      _next = {originalTarget.first  - mirrorA.first, 
                    originalTarget.second - mirrorA.second};
      this->tryUpdateCurLocation('o');
      ss<<*this<<" after deflection by Mirror at ["<< mirrorA<<"]\n";
    } // Now check expired mirrors
    for (auto & m: vec){
        if (--(m->ttl) == 0) _grid.del1mirror(m);
    }    
    return 0;
  }

  /* move1step() is another chokepoint. 
  
  We compute the distances to every mirror. 
  if any distance is 1 meter, then we have a directHit and absorption.
  otherwise collect those mirrors at distance 1.4142 meter, and pass them as a collection into indirectHit()
  
  Return value of 'a' indicates absorbed. All other return values not in use so far.
  */
  char move1step(){        
    std::vector<MirrorIterator> diagonalMirrors;
    for(auto itr = _grid.survivors.begin(); itr != _grid.survivors.end(); ++itr) {
      float dist = distanceTo(*itr);
      if (dist == 1) return directHit(itr); 
      if (isSqrt2(dist)) diagonalMirrors.push_back(itr); 
    }
    //ss<<diagonalMirrors.size()<<" = diagonalMirrors.size()\n";
    if (diagonalMirrors.size() == 0) return tryUpdateCurLocation(); // one step forward
    
    assert ( diagonalMirrors.size() < 3 && "3 or more diagonal mirrors ... are technically impossible" );
    return indirectHit( diagonalMirrors );
  }
  
public:  
  Photon(Cell const & c, Step const & n, Grid & g): _cur(c), _next(n), _grid(g){}
  std::string roundTrip(){ // returns the exit cell name
    _grid.leaveBreadcrumb(_cur, convertDirectiontoArrow());
    std::string exitCell = checkEdgeMirrors();
    if (exitCell.size() > 1) return exitCell;

    while(true){
      //ss<<*this<<" <-- before move1step\n";
      char status = this->move1step(); 
      if (status == ABSORBED) {
        ss<<*this<<"   <-- photon absorbed\n" ;
        return "";
      }
      if (isLeaving()){
        //ss<<*this<<"   <-- the last cell\n";
        return "{"+std::to_string(_cur.first)
              +","+std::to_string(_cur.second)+"}";
      }
    } // while
  } //function
};