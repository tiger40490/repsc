/* 
todo: populare from the file

This class doesn't need Photon.h
*/
#pragma once
#include "utils.h"
//#include "dumper.h" // needed for ?
#include <list>
#include <cassert>

struct Grid{ 
  RowId const length;
  std::list<Mirror> survivors; //the mirrors not yet expired.
  
  inline RowId minRowId() const{return 1;} //4 functions to enhance clarity of intent
  inline ColId minColId() const{return 1; }
  inline RowId maxRowId() const{return 1+length; }
  inline ColId maxColId() const{return 1+length; }
  
  size_t mirrorCnt() const{ return this->survivors.size(); }
  void del1mirror(MirrorIterator const it){
        assert(it->ttl == 0);
        survivors.erase(it);
        ss<<mirrorCnt()<<" = new mirrorCnt after removing an expired mirror\n";
  }
  // above function is faster and called from Photon class more often than the slow function below !
  void del1mirror_notInUse(Mirror const & m){
    assert(m.ttl == 0);
    for(auto itr = survivors.begin(); itr != survivors.end(); ++itr) {
      if (m.cell == itr->cell) del1mirror(itr);
    }
    assert(false && "should never reach here");
  }
};
