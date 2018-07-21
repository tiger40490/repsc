/* 
v0.9
*/
#ifndef E3_H
#define E3_H 1
#include <AbstractEngine.h>
#include <cmath>

/* Assuming symbol length is up to 13-characters (it is 3 in the current requirement), there can only be 26^13 symbols. Conceptually I can use a 13-D array where first subscript can be 0 (for 'a') to 25 (for 'z'). Same for 2nd subscript.... 

Implementation-wise, a flattened 1D array is easier. Therefore, a 64-bit int can qualify as an array index to address all the array elements, because 2^64 is greater than 26^13
*/
class Engine3: public AbstractEngine {
public:
  static size_t const symbolLen=3;
  static long   const arrayLen = static_cast<long>(pow(26,symbolLen)); 
  
  Engine3(){}
  Engine3(Engine3 const &) = delete; //public slight better
  Engine3 & operator=(Engine3 const &) = delete;
  
  virtual void save1tick(std::string const & symbol, TStamp tstamp, Quantity qty, Price px);
  virtual void printAscending() const;
private:
  PerSymbol * lookup[arrayLen]={nullptr};  
};
#endif
