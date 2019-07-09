#pragma once
#include "utils.h" 
#include <type_traits>

struct HasNewOid{}; struct HasPrice{}; struct HasSide{}; struct HasStock{};
// Above four types exist to enable overload resolution
template <class T> void castNewOid(T* sub, void * dummy){}
template <class T> void castNewOid(T* sub, HasNewOid * dummy){
    sub->oidNew = betoh(sub->oidNew);
    std::cout<<", replacement order id = "<<sub->oidNew;
}
template <class T> void castPrice(T* sub, void *,     T* dummy=nullptr, char mode='c'){}
template <class T> void castPrice(T* sub, HasPrice *, T* ser=nullptr, char mode='c'){
  if (mode == 'c'){
      sub->px4 = betoh(sub->px4);
      std::cout<<", px (scaled up by 10000) = "<<sub->px4;
  }else if (mode == 's'){
      ser->px4 = htobe(sub->px4);
  }
}
template<class T, size_t msgSz, bool hasPrice=false, bool hasSide=false,
                                bool hasStock=false, bool hasNewOid=false>
struct AbstractMsg{ 
  char const msgType; //not in use
  uint64_t nanos; //nanos since midnight
  uint64_t oid;

  T const * init(){
    using namespace std;
    static_assert( sizeof(T) == msgSz);
    T * sub = static_cast<T*>(this); // subclass non-const instance
    oid = betoh(oid); sub->qty = betoh(sub->qty); nanos = sinceEpoch(betoh(nanos));
    cout<<"oid = "<< oid<<", qty = "<<sub->qty<<", nanos since epoch = "<<nanos;
    castNewOid(sub, sub);
    castPrice(sub, sub);
    //cout<<", stock = "<<string(sub->stock, sub->stock+8)<<std::endl;
    //cout<<", side = "<<sub->side;
    //assert( (sub->side == 'S' || 'B' == sub->side)  && "Likely programmer error while parsing the SIDE field, as exchange would not send anything beside B or S" );
    return sub;
  }
  char* ser4test() const{ //return a serialized byte array
    T * sub = (T*)this; T clone(*sub);
    clone.oid = htobe(sub->oid);
    //if (hasNewOid) clone.oidNew = htobe(sub->oidNew);

    clone.qty = htobe(sub->qty);
    clone.nanos = htobe(sub->nanos%10000000000); // nanos since midnight
    castPrice(sub, sub, &clone, 's');
    static_assert( sizeof(T) == msgSz);
    auto ret = reinterpret_cast<char*> (&clone); dumpBuffer(ret, sizeof(T), "serialized msg");
    return ret;
  }
} __attribute__((packed));

struct AddOrderMsg: public AbstractMsg<AddOrderMsg, 34, true,true,true>, public HasPrice{
  char const side; uint32_t qty; char const stock[8];
  uint32_t px4; //price scaled up by 10, four times
} __attribute__((packed));
struct DecOrderMsg: public AbstractMsg<DecOrderMsg, 21>{
  uint32_t qty;
} __attribute__((packed));
struct ExeOrderMsg: public AbstractMsg<ExeOrderMsg, 21>{ //identical to DecOrderMsg, but can become different in the future
  uint32_t qty;
} __attribute__((packed));
struct RepOrderMsg: public AbstractMsg<RepOrderMsg, 33, true,false,false,true>{
  uint64_t oidNew;
  uint32_t qty;
  uint32_t px4;
} __attribute__((packed));
