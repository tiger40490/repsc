#pragma once
#include "messages.h" // to see the content of AddOrderMsg
#include <cassert>
#include <iostream>

class Parser; //#include "Parser.h" //circular dependency ... must use forward declaration

struct Order{ // not a Msg or Event object, but a plain old struct
  uint32_t px4;
  uint32_t qty; 
  std::string const stock;
  //char side; //not needed, also order id

  Order(): Order(0,0,std::string()){} //needed in STL

  Order(AddOrderMsg const * msg): Order(msg->px4, msg->qty, std::string(msg->stock, msg->stock+8)) {
    Parser::record("o+#" + std::to_string(msg->oid), qty, stock);
  }

  friend std::ostream & operator<<(std::ostream & os, Order const & i){
    os<<"Order{ q= "<<i.qty<<" , p(int)= "<<i.px4<<" , stock= "<<i.stock<<"}";
    return os;
  }

private:

  Order(uint32_t p, uint32_t q, std::string s): px4(p), qty(q), stock(s){
//    std::cout<<stock<<qty<<" <-- an order for this stock has been created .. ";    
  }
}; 
