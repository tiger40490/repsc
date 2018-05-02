// v0.9
#ifndef E1_H
#define E1_H 1
#include <AbstractEngine.h>
#include <Tick.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
// using namespace std; //should NOT put this in header!

class Engine1: public AbstractEngine{ // simple query engine
  Engine1(Engine1 const &);
  Engine1 & operator=(Engine1 const &);

protected:
  typedef std::map<std::string, std::vector<Tick const*> > String2VectorType; 

  // for each symbol, there's a vector holding all the Tick objects
  // This data structure holds all the data in the tick file.
  //
  // I believe each Tick object has to be saved right after construction
  // on the heap, regardless of optimization mode.
  String2VectorType bigMap; 

public:
  Engine1(){}
  void getSymbolsInBigMap(); 
  virtual char tickfile(std::string const & filename ); 

  virtual char print  (unsigned int const ts1,
                       unsigned int const ts2,
                       std::string const & symbol );

  virtual char product(unsigned int const ts1, 
                       unsigned int const ts2, 
                       std::string const & symbol, 
                       std::string const & f1 , 
                       std::string const & f2 );
};

#endif
