#pragma once

#include "AddOrderMsg.h"
#include <cassert>
#include <iostream>
struct Order{
  uint32_t const px4, qty; 
  std::string const stock;
  //char side; //not needed, also order id
  Order(AddOrderMsg const * msg): Order(msg->px4, msg->qty, std::string(msg->stock, msg->stock+8)) {
  }
private:
  Order(uint32_t p, uint32_t q, std::string s): px4(p), qty(q), stock(s){
    std::cout<<stock<<" <-- an order for this stock has been created .. ";    
  }
  // add non-static methods to output something? 
}; 
