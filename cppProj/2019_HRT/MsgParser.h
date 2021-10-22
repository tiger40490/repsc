#pragma once
#include <iostream>
#include <cstddef> //size_t

struct MsgParser{ 
  size_t const msgSz; 
  virtual char parse(char *buf) = 0; //buffer length is guaranteed to be sufficient

protected:
  MsgParser(size_t sz): msgSz(sz){}
};
