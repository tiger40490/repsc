#pragma once

#include "OrderMsg.h"
#include <cassert>
#include <iostream>

//#include "Parser.h" //circular dependency ... must use forward declaration
struct Parser;

// not an Msg or Event object
struct Order{
  uint32_t const px4, qty; 
  std::string const stock;
  //char side; //not needed, also order id

  Order(AddOrderMsg const * msg): Order(msg->px4, msg->qty, std::string(msg->stock, msg->stock+8)) {
    Parser::record("o+#" + std::to_string(msg->oid), qty, stock);
  }
private:
  Order(uint32_t p, uint32_t q, std::string s): px4(p), qty(q), stock(s){
    std::cout<<stock<<qty<<" <-- an order for this stock has been created .. ";    
  }
  // add non-static methods to output something? 
}; 
