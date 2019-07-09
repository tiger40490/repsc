#pragma once
#include "utils.h" 

template<class T, bool hasPrice=false, bool hasSide=false,
                  bool hasStock=false, bool hasNewOid=false>
struct AbstractMsg{ 
  char const msgType; //not in use
  uint64_t nanos; //nanos since midnight
  uint64_t oid;

  T const * cleanup(){
    using namespace std;
    T * sub = static_cast<T*>(this); // subclass non-const instance
    oid = betoh(oid); sub->qty = betoh(sub->qty); nanos = sinceEpoch(betoh(nanos));
    cout<<"oid = "<< oid<<", qty = "<<sub->qty<<", nanos since epoch = "<<nanos;
    if (hasNewOid){ //todo
    }

    if (hasPrice){
      sub->px4 = betoh(sub->px4);
      cout<<", px (scaled up by 10000) = "<<sub->px4;
    }
    if (hasSide)  cout<<", side = "<<sub->side;
    if (hasStock) cout<<", stock = "<<string(sub->stock, sub->stock+8)<<std::endl;
    assert( (sub->side == 'S' || 'B' == sub->side)  && "Likely programmer error while parsing the SIDE field, as exchange would not send anything beside B or S" );
    return sub;
  }

  char* ser4test() const{ //serialize to a byte array
    T const* sub = static_cast<T const*>(this);
    T clone(*sub);
    clone.oid = htobe(sub->oid);
    clone.qty = htobe(sub->qty);
    clone.px4 = htobe(sub->px4);
    clone.nanos = htobe(sub->nanos%10000000000);
    auto ret = reinterpret_cast<char*> (&clone);
    dumpBuffer(ret, sizeof(T), "serialized msg");
    return ret;
  }
} __attribute__((packed));

struct AddOrderMsg: public AbstractMsg<AddOrderMsg, true,true,true>{
  char const side; uint32_t qty; char const stock[8];
  uint32_t px4; //price scaled up by 10, four times
} __attribute__((packed));

