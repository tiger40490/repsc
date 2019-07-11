#pragma once
#include "utils.h" 
#include <type_traits>

struct HasPrice{}; //struct HasSide{}; struct HasStock{}; struct HasNewOid{}; 

template <class T> void castPrice(T* sub,  void const*,    T* _  =nullptr, char mode='c'){ throw std::string("This overload should never get picked up"); }

template <class T> void castPrice(T* sub, HasPrice const*, T* ser=nullptr, char mode='c'){
  if (mode == 'c'){ //cast to host endianness
      sub->px4 = betoh(sub->px4);
      std::cout<<", px4 (scaled up by 10000) = "<<sub->px4;
  }else if (mode == 's'){ //serialize to big-endian
      assert (ser != sub && "Programmer error");
      assert (ser != nullptr && "Programmer error");
      ser->px4 = htobe(sub->px4);
  }
}
////// Code above is tricky but simple template metaprogramming /////

template<class T, size_t msgSz, bool hasPrice=false, bool hasSide=false,
                                bool hasStock=false, bool hasNewOid=false>
struct AbstractMsg{ 
  char const msgType; //for ser4test() only
  uint64_t nanos; //nanosecond since midnight
  uint64_t oid;
  char         side_() const{ throw std::string("unsupported"); } //required at compile time
  std::string stock_() const{ throw std::string("unsupported"); } //required at compile time
  uint64_t serNewOid4test(T const* sub){  throw std::string("unsupported"); }
  void deserNewOid()        { throw std::string("unsupported"); }

  T const * init(){
    using namespace std;
    static_assert( sizeof(T) == msgSz);
    T * sub = static_cast<T*>(this); // subclass non-const instance
    oid = betoh(oid); 
    nanos = sinceEpoch(betoh(nanos));
    sub->qty = betoh(sub->qty); 
    cout<<"oid = "<< oid<<", qty = "<<sub->qty<<", nanos since epoch = "<<nanos;

    if (hasNewOid) sub->deserNewOid();
    if (hasPrice ) castPrice(sub, sub);
    if (hasStock) cout<<", stock = "<<sub->stock_();
    if (hasSide){
      char const orderSide = sub->side_(); cout<<", side = "<<orderSide;
      assert( (orderSide == 'S' || 'B' == orderSide)  && "Likely programmer error while parsing the SIDE field, as exchange would not send anything beside B or S" );
    }
    cout<<endl;
    return sub;
  }
  char* ser4test(char* tgt=nullptr) const{ //basically the reverse of init(): return a serialized byte array to created a test msg, for testing only, not for production
    //T const* sub = (T*)this;
    T const* sub = static_cast<T const*>(this);
    T clone(*sub); //bitwise clone
    clone.oid = htobe(sub->oid);
    clone.qty = htobe(sub->qty);
    clone.nanos = htobe(sub->nanos% (24*3600*1000*1000*1000)); // nanos since midnight
    if (hasPrice) castPrice(const_cast<T*>(sub), sub, &clone, 's');
    if (hasNewOid) clone.serNewOid4test(sub);
    static_assert( sizeof(T) == msgSz);
    auto ret = reinterpret_cast<char*> (&clone); dumpBuffer(ret, sizeof(T), "serialized msg (BE) for test");
    if (tgt) {
      memcpy(tgt, ret, msgSz);
      std::cout<<msgSz<<" = memcpy byte count\n";
    }
    return tgt;
  }
} __attribute__((packed));

struct RepOrderMsg: public AbstractMsg<RepOrderMsg, 33, true,false,false,true>, public HasPrice{
  uint64_t oidNew; uint32_t qty; uint32_t px4;
  void serNewOid4test(RepOrderMsg const* sub){ this->oidNew = htobe(sub->oidNew); }
  void deserNewOid(){
    oidNew = betoh(oidNew); 
    std::cout<<", replacement order id = "<<oidNew;
  }
  static char* fakeMsg(uint64_t h_oid, uint64_t h_oidNew, uint32_t h_qty, uint64_t h_nanos, uint32_t h_px4){ //h_ means in host endianness
using namespace std;
    static size_t const sz=sizeof(RepOrderMsg);
    static char serBuf[sz]; //to be overwritten each time
    RepOrderMsg msg={'R', h_nanos, h_oid, {}, h_oidNew, h_qty, h_px4};
    msg.ser4test(serBuf); //dumpBuffer(serBuf, sz, "serialized fake Rep msg");
    return serBuf;
  }
} __attribute__((packed));

struct DecOrderMsg: public AbstractMsg<DecOrderMsg, 21>{
  uint32_t qty;
  static char* fakeMsg(uint64_t h_oid, uint32_t h_qty, uint64_t h_nanos){ //h_ means in host endianness
    static size_t const sz=sizeof(DecOrderMsg);
    static char serBuf[sz]; //to be overwritten each time
    DecOrderMsg msg={'X', h_nanos, h_oid, h_qty };
    msg.ser4test(serBuf); //dumpBuffer(serBuf, sz, "serialized fake Dec msg");
    return serBuf;
  }
} __attribute__((packed));

struct ExeOrderMsg: public AbstractMsg<ExeOrderMsg, 21>{ //identical to DecOrderMsg, but can become different in the future
  uint32_t qty;
} __attribute__((packed));

struct AddOrderMsg: public AbstractMsg<AddOrderMsg, 34, true,true,true>, public HasPrice{
  char const side; uint32_t qty; char const stock[8];
  uint32_t px4; //price scaled up by 10, four times
  char side_() const {return side; }
  std::string stock_() const {return std::string(stock, stock+8); }
} __attribute__((packed));
