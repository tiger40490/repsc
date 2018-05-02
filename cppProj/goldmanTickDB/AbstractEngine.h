// v1.0
#ifndef AE_H
#define AE_H 1

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

struct comma_is_space : std::ctype<char> { //use comma as delimiter 
  comma_is_space() : std::ctype<char>(get_table()) {}
  static mask const* get_table() {
    static mask rc[table_size];
    rc[','] = std::ctype_base::space;
    return &rc[0];
  }
};

struct AbstractEngine{
  virtual char tickfile(std::string const & filename ) = 0;
  virtual char print  (unsigned int const ts1, 
                       unsigned int const ts2, 
                       std::string const & symbol ) = 0;
  virtual char product(unsigned int const ts1, 
                       unsigned int const ts2, 
                       std::string const & symbol, 
                       std::string const & f1 , 
                       std::string const & f2 ) = 0;
  AbstractEngine(){}
  virtual ~AbstractEngine(){}
private:
  AbstractEngine(AbstractEngine const &);
  AbstractEngine & operator=(AbstractEngine const &);
};

#endif
