#ifndef E1_H
#define E1_H 1
#include <AbstractEngine.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

struct Engine1: public AbstractEngine { // simple query engine
public:
  Engine1(){}
  Engine1(Engine1 const &) = delete;
  Engine1 & operator=(Engine1 const &) = delete;
  
  virtual char tickfile(std::string const & filename ); 
};

#endif
