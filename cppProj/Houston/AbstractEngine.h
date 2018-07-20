/* 
Q: Why do we need this class? 
A: Extensibility -- Another engine can override the virtual functions to implement a different algorithm.
*/
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
  AbstractEngine(){}
  virtual ~AbstractEngine(){}
  virtual char tickfile(std::string const & filename ) = 0;
  virtual int getMaxPx(std::string const & symbol){return 0;}
  AbstractEngine(AbstractEngine const &) = delete;
  AbstractEngine & operator=(AbstractEngine const &) = delete;
};

#endif
