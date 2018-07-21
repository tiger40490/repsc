/*todo: "3" to become a template paramter
todo: use vector and unique_ptr

Assuming symbol length is 3, there can only be 26^3 symbols. A 64-bit int can be an array index to address all of them.
*/
#ifndef E3_H
#define E3_H 1
#include <AbstractEngine.h>
#include <cmath>

struct Engine3: public AbstractEngine { // simple query engine
  static size_t const symbolLen=3;
  PerSymbol * lookup[static_cast<long>(pow(26,symbolLen))]={nullptr};
  
public:
  Engine3(){}
  Engine3(Engine3 const &) = delete;
  Engine3 & operator=(Engine3 const &) = delete;
  
  virtual void save1tick(std::string const & symbol, TStamp tstamp, Quantity qty, Price px);
  virtual void printAscending() const;
};

#endif
