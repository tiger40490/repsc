/* 
Q: Why do we need this class? 
A: Extensibility -- Another engine can override the virtual functions to implement a different algorithm.

v0.90
*/
#ifndef AE_H
#define AE_H 1

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>
using TStamp = long long;
using Quantity = long long;
using Price = int;

struct PerSymbol{
  PerSymbol(TStamp _ts, Quantity _q, Price _p):
    maxGap(0), 
    lastUpd(_ts), 
    cum$vol(_q*_p), //dollar amount traded
    cumVol(_q),
    maxPx(_p){}
    
  consumeTick(TStamp _ts, Quantity _q, Price _p){
    assert (_ts > lastUpd);
    auto gap = _ts - lastUpd;
    if (gap > maxGap) maxGap = gap;
    lastUpd = _ts;

    if (_p > maxPx) maxPx = _p;
    cumVol += _q;
    cum$vol += _q*_p;
  }
  friend std::ostream & operator<<(std::ostream & os, PerSymbol const * rec){
    auto avg = rec->cum$vol/rec->cumVol; //truncated
    os<<rec->maxGap<<","<<rec->cumVol<<","<<avg<<","<<rec->maxPx;
    return os;
  }
private:    
  TStamp maxGap, lastUpd;
  long long cum$vol;
  Quantity  cumVol;
  Price maxPx;
};

class AbstractEngine{
public:
  AbstractEngine(){}
  virtual ~AbstractEngine(){}
  AbstractEngine(AbstractEngine const &) = delete;
  AbstractEngine & operator=(AbstractEngine const &) = delete;
  
  virtual void save1tick(std::string const & symbol, TStamp tstamp, Quantity qty, Price px) = 0;
  virtual void printAscending(std::ofstream & outfile) const = 0;
  virtual char tickfile(std::string const & filename );
};

#endif
