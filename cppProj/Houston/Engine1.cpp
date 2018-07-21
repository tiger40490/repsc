/*
v1
*/

#include <Engine1.h>
using namespace std;

void Engine1::save1tick(std::string const & symbol, TStamp tstamp, Quantity qty, Price px){
  auto found = this->lookup.find(symbol);
  if (found == this->lookup.end()){
    //make_unique is possibly better but my compiler doesn't support make_unique
    auto rec = make_shared<PerSymbol>(tstamp, qty, px);
    
    this->lookup.insert(make_pair(symbol, rec));
    cout<<symbol<<" created + "<<rec.get()<<endl;
  }else{
    auto rec = found->second;
    rec->consumeTick(tstamp, qty, px);
    cout<<symbol<<" updated "<<rec.get()<<endl;
  }
}

void Engine1::printAscending(ofstream & outfile) const{
  cout<<"--- Engine1 printAscending ---\n";

  for (auto const & entry: this->lookup){ //not an iterator
      outfile<<entry.first<<","<<entry.second.get()<<endl;
      cout   <<entry.first<<","<<entry.second.get()<<endl;
  }
}