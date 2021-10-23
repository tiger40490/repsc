/* 
todo: populare from the file

This class doesn't need Photon.h
*/
#pragma once
#include "utils.h"
//#include "dumper.h" // needed for ?
#include <list>
//#include <cmath>
//#include <iostream>
#include <cassert>

struct Grid{ 
  RowId const length;
  std::list<Mirror> survivors; //the mirrors not yet expired.
  
  size_t mirrorCnt() const{ return this->survivors.size(); }
  
  void del1mirror(Mirror const & m){
    assert(m.ttl == 0);
    for(auto itr = survivors.cbegin(); itr != survivors.cend(); ++itr) {
      if (m.cell == itr->cell){
        survivors.erase(itr);
        ss<<mirrorCnt()<<" = new mirrorCnt after removing an expired mirror\n";
        return ;
      }
    }
    assert(false && "should never reach here");
  }
};
