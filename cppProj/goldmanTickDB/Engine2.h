// v0.9
#ifndef E2_H
#define E2_H 1
#include <Engine1.h>
#include <Tick.h>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
// using namespace std; //should NOT put this in header!

class Engine2: public Engine1{ //a more complex query engine, with special product() implementation
  typedef std::map<std::string, String2VectorType> String2vectorType;
  String2vectorType symbol2field2vector;


  Engine2(Engine2 const &);
  Engine2 & operator=(Engine2 const &);

public:
  Engine2(){}
  virtual char tickfile(std::string const & filename ); 

  //print() is same as inherited
  
  virtual char product(unsigned int const ts1,
                       unsigned int const ts2,
                       std::string const & symbol,
                       std::string const & f1 ,
                       std::string const & f2 );
};

#endif
