/* 
v0.9
*/
#include <Engine3.h>
using namespace std;

static long symbolToSubscript(string const & symbol){
  assert(symbol.size() <= Engine3::symbolLen);
  long ret = 0;
  for(char c: symbol) ret = ret*26 + c-'a';
  return ret;  
}
static void subscriptToSymbol(long subscript, char * buf){
  assert (subscript < Engine3::arrayLen);
  for(int i=Engine3::symbolLen-1; i>=0; --i){
    //assert (buf[i] == '\0' && "should be initialized to nulls");
    buf[i] = subscript % 26 + 'a';
    subscript /= 26;
  }
}
///// Above are two private utility functions
void Engine3::save1tick(std::string const & symbol, TStamp tstamp, Quantity qty, Price px){
  auto subscript = symbolToSubscript(symbol);
  auto & ptr = this->lookup[subscript];
  if (ptr){
    ptr->consumeTick(tstamp, qty, px);
    //cout<<symbol<<" updated "<<ptr<<endl;
  }else{
    auto ptr = new PerSymbol(tstamp, qty, px);//deleted in Engine3 dtor
    this->lookup[subscript] = ptr;
    //cout<<symbol<<" created "<<ptr<<endl;
  }
}

void Engine3::printAscending(ofstream & outfile) const{
  cout<<"--- Engine-3 printAscending ---\n";
  
  //Warning: symbol variable must be iniialized inside the for-loop if symbols can have different lengths !
  char symbol[ Engine3::symbolLen +1 ]={'\0'};
  
  for (long i=0; i<Engine3::arrayLen; ++i){
    subscriptToSymbol(i, symbol);
    if (this->lookup[i]){
      outfile<<symbol<<","<<this->lookup[i]<<endl;
      cout   <<symbol<<","<<this->lookup[i]<<endl;
    }
  }
}