#include <Engine3.h>
using namespace std;

static long symbolToIndex(string const & symbol){
  assert(symbol.size() <= Engine3::symbolLen);
  long ret = 0;
  for(char c: symbol)
    ret = ret*26 + c-'a';
  return ret;  
}

static void indexToSymbol(long index, char * buf){
  for(int i=Engine3::symbolLen-1; i>=0; --i){
    buf[i] = index % 26 + 'a';
    index = index/26;
  }
}

void Engine3::save1tick(std::string const & symbol, TStamp tstamp, Quantity qty, Price px){
  auto index = symbolToIndex(symbol);
  auto & ptr = this->lookup[index];
  if (ptr){
    ptr->consumeTick(tstamp, qty, px);
    cout<<symbol<<" updated "<<ptr<<endl;
  }else{
    auto ptr = new PerSymbol(tstamp, qty, px);
    this->lookup[index] = ptr;
    cout<<symbol<<" created "<<ptr<<endl;
  }
}

void Engine3::printAscending() const{
  for (long i=0; i<pow(26,symbolLen); ++i){
    char symbol[Engine3::symbolLen+1]={'\0'};
    indexToSymbol(i, symbol);
    if (this->lookup[i])
      cout<<symbol<<","<<this->lookup[i]<<endl;
  }
}