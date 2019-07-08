#pragma once

#include <cassert>
#include <iostream>
struct Order{
  uint32_t const px4, qty; 
  std::string const stock;
  //char side; //not needed, also order id
  Order(uint32_t p, uint32_t q, std::string s): px4(p), qty(q), stock(s){
  }
  // add non-static methods to output something? 
}; 
