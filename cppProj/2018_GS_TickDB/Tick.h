// v0.9
#ifndef TICK_H
#define TICK_H 1
#include <Field.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

struct FieldNameComp{ //not in use
  bool operator() (std::shared_ptr<Field> const & a, std::shared_ptr<Field> const & b) const{
    return a->name() < b->name();
  }
};

// There will be a large number of Tick objects.
// Each unique Tick is always allocated exactly once, on heap. 
// Its address is saved in various data stores.
struct Tick{
  typedef std::map<Field const*, double> FieldMapType;
  unsigned int const timestamp;

  void    addField(std::string const & name, double   value) const;
  bool lookupField(std::string const & name, double & value) const;

  static Tick const * newTick(unsigned int timestamp, std::string const & symbol);


  //I decided to put these modifed-binary-search utilities in Tick class instead of Engine classes, because
  //Tick pointers will be invariably stored in some vectors, even if there's no query engine.
  static int  bsearch (std::vector<Tick const*> const & vec, unsigned int const timestamp, bool isLowerSide);
  static char bsearch2(std::vector<Tick const*> const & , int & pos1, int & pos2,
                  unsigned int const ts1,
                  unsigned int const ts2, std::string const & identifier);


  friend std::ostream & operator<<(std::ostream & os, Tick const & t);

private:
  FieldMapType mutable fmap; 


  // restrict construction to the heap
  Tick(unsigned int t, std::string const & s): timestamp(t) {}; //, symbol(s) {}
  Tick(Tick const &);
  Tick & operator=(Tick const &);
  ~Tick();
};

#endif
