/* 
showcase member typedef

This class logically doesn't need Photon.h. 
Logical simplicity, but implementation complexity
*/
#pragma once
#include "utils.h"

static char const EMPTY_CELL=' ';
static char const MIRROR_CELL='M';

struct Grid{ 
  Coordinate_t const length; //
  std::list<Mirror> survivors; //the mirrors not yet erased
  std::vector<std::vector<char> > printable; //visualization
  /// 
  typedef std::string RayDescriptor;
  typedef std::string TestResult;
  typedef std::pair<RayDescriptor, TestResult> TestCase;
  std::list<TestCase> fullOutputToPrint;
  
  size_t mirrorCnt() const{ return this->survivors.size(); }
  void del1mirror(MirrorIterator const it){ //tested 1x
        assert(it->ttl == 0);
        survivors.erase(it); // list::erase() does NOT invalidate other iterators to be erased :)
        Cell const & addr = it->address;
        printable[addr.first][addr.second] = EMPTY_CELL;
        ss<<mirrorCnt()<<" = mirrorCnt after removing one expired mirror\n";
  }
  void dumpFullOutputToStdErr() const{ 
    for (auto const & record: fullOutputToPrint){
      std::cerr<<record.first<<" -> "<<record.second<<"\n";
    }      
  }
  void printGrid() const{
    std::stringstream ret;
    ret<<"\n-----------------------\n | ";
    for (int c=0; c<=length+1; ++c) ret<<' '<<c;
    
    for (int r=0; r<=length+1; ++r){
      ret<<"\n"<<r<<"| ";
      for (int c=0; c<=length+1; ++c){
        ret<<' '<<printable[r][c];
      }
    }
    ret<<"\n | ";
    for (int c=0; c<=length+1; ++c) ret<<' '<<c;
    ret<<"\n-----------------------\n";
    ss<<ret.str();
    return;
  }
  void updatePrintable(Cell const & addr, char ch){
    assert(maxXY(addr) <= length+1);
    char & existing = printable[addr.first][addr.second];
        
    if     (existing + ch == '^' + 'v') existing = '|';
    else if(existing + ch == '>' + '<') existing = '=';
    else                                existing = ch;
  }
  void leaveBreadcrumb(Cell const & photonLocation, char arrow){
    updatePrintable(photonLocation, arrow);
    printGrid();
  }
  void initPrintable(){
      printable = std::vector<std::vector<char> >(
        length+2, 
        std::vector<char>(length+2, EMPTY_CELL)
      );
      for (auto const & m: survivors){
        Cell const & addr = m.address;
        updatePrintable(addr, MIRROR_CELL);
      }
      printGrid();
  }
  void clearBreadcrumb(){
    for (int r=0; r<=length+1; ++r){
      for (int c=0; c<=length+1; ++c){
        if (printable[r][c] != MIRROR_CELL)
            printable[r][c] = EMPTY_CELL;
      }
    }      
  }
  // factory method
  static Grid* parse2files(std::string const & fM /*mirrors*/, std::string const & fT /*tests*/){
    std::string line;
    std::stringstream stream(fM); //stringstream works like a filestream.
    Grid * ret;
    for (size_t ln=0; std::getline(stream, line); ){
      //if (line[0] == '#') continue;
      if (line.size() == 0) continue;
      if ( !std::isdigit(line[0]) ) continue; //ignore any line not started with a digit
      //ss<<line.c_str()<<"\n";
      if (++ln == 1) {
        ret = new Grid{ (Coordinate_t) std::stoi(line)};
        //ret->length = ;
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
      ret->survivors.push_back( 
          {{tokens[0],tokens[1]},   sz==3? tokens[2]:-99} );
      //ss<<ret->survivors.back()<<" is a new mirror from file input\n";
    }//for
    ret->initPrintable();
    //ss<<survivors<<" ... are the initial mirrors created from file input\n";
    stream = std::stringstream(fT);
    for (; std::getline(stream, line); ){
      if (line.size() == 0) continue;
      if ( line[0] !='C' &&  line[0] !='R' ) continue; //anything unrecognized is assumed to be comment
      ret->fullOutputToPrint.push_back({line, "pending"});
    }
    //ret->dumpFullOutputToStdErr();
    assert(ret && "return value must not be nullptr");
    return ret;
  }//function
};
