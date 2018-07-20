/* 
Q: Why do we need this class? 
A: Extensibility -- Another engine can override the virtual functions to implement a different algorithm.
*/
#ifndef AE_H
#define AE_H 1

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

struct AbstractEngine{
  AbstractEngine(){}
  virtual ~AbstractEngine(){}
  virtual char tickfile(std::string const & filename ) = 0;
  virtual int getMaxPx(std::string const & symbol){return 0;}
  AbstractEngine(AbstractEngine const &) = delete;
  AbstractEngine & operator=(AbstractEngine const &) = delete;
};

#endif
