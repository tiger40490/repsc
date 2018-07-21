/* 
v0.9
*/
#ifndef E3_H
#define E3_H 1
#include <AbstractEngine.h>
#include <cmath>

/* This engine is based on a sorted array.

Array is generally faster than hash table due to 
1) cache efficiency
2) smaller footprint
3) guaranteed constant-time access, not subject to hashcode distribution

My array is inherently sorted by symbol.

Assuming symbol length is up to 13-characters (It is 3 in the current requirement.), there can only exist 26^13 symbols. Conceptually we can use a 13-D array where first subscript can be 0 (for 'a') to 25 (for 'z'). Same for 2nd subscript...

Implementation-wise, a flattened 1D array is chosen. Therefore, a 64-bit int can qualify as an array index to address all the array elements, because 2^64 is greater than 26^13.

(Tradeoff) However, my array is sparse, leading to more waste of memory compared to hash table. The unused array elements are filled with null pointers, probably 8 bytes each in a 64-bit machine.

(Tradeoff) Storing unique_ptr instead of raw pointer would take up more than 8 bytes each, but would automate memory deallocation.
*/
class Engine3: public AbstractEngine {
public:
  static size_t const symbolLen=3;
  static long   const arrayLen = static_cast<long>(pow(26,symbolLen)); 
  
  Engine3(){}
  ~Engine3(){
    std::cout<<"Engin3 dtor\n";
    for (long i=0; i<Engine3::arrayLen; ++i){
      delete lookup[i];
    }
  }
  Engine3(Engine3 const &) = delete; //public slight better than private
  Engine3 & operator=(Engine3 const &) = delete;
  
  virtual void save1tick(std::string const & symbol, TStamp tstamp, Quantity qty, Price px);
  virtual void printAscending(std::ofstream & outfile) const;
private:
  PerSymbol * lookup[arrayLen]={nullptr};  
};
#endif
