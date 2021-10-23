/* 
todo: populare from the file

This class doesn't need Photon.h
*/
#pragma once
#include "utils.h"
//#include "dumper.h" // needed for ?
#include <list>
//#include <cmath>
//#include <iostream>
#include <cassert>

struct Grid{ 
  unsigned int const length;
  std::list<Mirror> survivors; //the mirrors not yet expired.
};
