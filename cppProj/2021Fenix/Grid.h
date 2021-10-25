/* 

This class doesn't need Photon.h
*/
#pragma once
#include "utils.h"
//#include "dumper.h" // needed for ?
#include <list>
#include <cassert>

struct Grid{ 
  Coordinate_t length; //todo: should be a const
  std::list<Mirror> survivors; //the mirrors not yet erased
  
  typedef std::string RayDescriptor;
  typedef std::string TestResult;
  typedef std::pair<RayDescriptor, TestResult> TestCase;
  std::list<TestCase> fullOutputToPrint;
  
  size_t mirrorCnt() const{ return this->survivors.size(); }
  void del1mirror(MirrorIterator const it){ //tested 1x
        assert(it->ttl == 0);
        survivors.erase(it); // list::erase() does NOT invalidate other iterators to be erased :)
        ss<<mirrorCnt()<<" = mirrorCnt after removing one expired mirror\n";
  }
  void dumpFullOutputToStdErr() const{ 
    for (auto const & record: fullOutputToPrint){
      std::cerr<<record.first<<" -> "<<record.second<<"\n";
    }      
  }
  void parse2files(std::string const & fM /*mirrors*/, std::string const & fT /*tests*/){
    std::string line;
    std::stringstream stream(fM); //stringstream works like a filestream.
    for (size_t ln=0; std::getline(stream, line); ){
      //if (line[0] == '#') continue;
      if (line.size() == 0) continue;
      if ( !std::isdigit(line[0]) ) continue; //ignore any line not started with a digit
      //ss<<line.c_str()<<"\n";
      if (++ln == 1) {
        this->length = std::stoi(line);
        //ss<<length<<" = the new grid dimension\n";
        continue;
      }
      //split into 2 or 3 tokens
      std::stringstream lineStream(line);
      std::vector<int> tokens;
      std::string token;
      while(std::getline(lineStream, token, ' ')){
        tokens.push_back(std::stoi(token));
      }
      //ss<<tokens;
      size_t const sz = tokens.size();
      assert (sz==2 || 3==sz);
      this->survivors.push_back( 
          {{tokens[0],tokens[1]},   sz==3? tokens[2]:-99} );
      //ss<<this->survivors.back()<<" is a new mirror from file input\n";
    }//for
    //ss<<survivors<<" ... are the initial mirrors created from file input\n";
    stream = std::stringstream(fT);
    for (; std::getline(stream, line); ){
      if (line.size() == 0) continue;
      if ( line[0] !='C' &&  line[0] !='R' ) continue; //anything unrecognized is assumed to be comment
      fullOutputToPrint.push_back({line, "pending"});
    }
    //this->dumpFullOutputToStdErr();
  }//function
};
