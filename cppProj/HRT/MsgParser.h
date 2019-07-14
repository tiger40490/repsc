#pragma once
#include "Parser.h"
#include "Order.h"
#include "BaseEvent.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <cstddef> //size_t
#include <cassert>

struct MsgParser{ 
  size_t const msgSz; 
  virtual char parse(char *buf) = 0; //no buffer len needed .. guaranteed to be sufficient

protected:
  MsgParser(size_t sz): msgSz(sz){}
};

