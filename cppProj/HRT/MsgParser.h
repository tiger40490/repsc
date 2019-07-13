#pragma once
#include <cstddef> //size_t

struct MsgParser{ //StatelessMsgParser
  size_t const msgSz; 
  virtual char parse(char *buf) = 0; //no buffer len needed .. guaranteed to be sufficient
protected:
  MsgParser(size_t sz): msgSz(sz){}
};
