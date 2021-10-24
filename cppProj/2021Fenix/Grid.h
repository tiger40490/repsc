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
  RowId length;
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
  void parse2files(std::string const & fM /*mirrors*/, std::string const & fT /*tests*/){
    std::string line;
    std::stringstream stream(fM);
    for (size_t ln=0; std::getline(stream, line); ){
      //if (line[0] == '#') continue;
      if (line.size() == 0) continue;
      if ( !std::isdigit(line[0]) ) continue; //ignore any line not started with a digit
      //ss<<line.c_str()<<"\n";
      if (++ln == 1) {
        this->length = std::stoi(line);
        ss<<length<<" = the new grid dimension\n";
        continue;
      }
      //split into 2 or 3 tokens
      std::stringstream lstream(line);
      std::vector<int> a;
      std::string token;
      while(std::getline(lstream, token, ' ')){
        a.push_back(std::stoi(token));
      }
      ss<<a;
      size_t const sz = a.size();
      assert (sz==2 || 3==sz);
      Mirror m = {{a[0], a[1]},   sz==3? a[2]:-99};
      ss<<m<<" is a new mirror from file input\n";
      this->survivors.push_back(m);
    }//for
  }
  
};
