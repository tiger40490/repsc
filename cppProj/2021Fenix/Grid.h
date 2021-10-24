/* 
todo: populare from the file
todo: remove unused function

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
  
//  inline RowId minRowId() const{return 1;} //4 functions to enhance clarity of intent
  //inline ColId minColId() const{return 1; }
//  inline RowId maxRowId() const{return 1+length; }
  //inline ColId maxColId() const{return 1+length; }
  
  size_t mirrorCnt() const{ return this->survivors.size(); }
  void del1mirror(MirrorIterator const it){
        assert(it->ttl == 0);
        survivors.erase(it); // list::erase() does NOT invalidate other iterators to be erased :)
        ss<<mirrorCnt()<<" = mirrorCnt after removing one expired mirror\n";
  }
};
