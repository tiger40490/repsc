#ifndef E1_H
#define E1_H 1
#include <AbstractEngine.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
// using namespace std; //should NOT put this in header!

class Engine1: public AbstractEngine { // simple query engine
  Engine1(Engine1 const &);
  Engine1 & operator=(Engine1 const &);

public:
  Engine1(){}
  virtual char tickfile(std::string const & filename ); 
};

#endif
