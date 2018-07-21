#ifndef E1_H
#define E1_H 1
#include <AbstractEngine.h>
#include <map>
#include <memory>

struct Engine1: public AbstractEngine { // simple query engine
  std::map<std::string, std::shared_ptr<PerSymbol> > lookup;
  
public:
  Engine1(){}
  Engine1(Engine1 const &) = delete;
  Engine1 & operator=(Engine1 const &) = delete;
  
  virtual void save1tick(std::string const & symbol, TStamp tstamp, Quantity qty, Price px);
};

#endif
