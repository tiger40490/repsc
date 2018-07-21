/*todo: try unique_ptr
*/

#include <Engine1.h>
using namespace std;

void Engine1::save1tick(std::string const & symbol, TStamp tstamp, Quantity qty, Price px){
  auto found = this->lookup.find(symbol);
  if (found == this->lookup.end()){
    //make_unique is possibly better but my compiler doesn't support make_unique
    auto rec = make_shared<PerSymbol>(tstamp, qty, px);
    cout<<symbol<<" created "<<rec.get()<<endl;
    this->lookup.insert(make_pair(symbol, rec));
  }else{
    auto rec = found->second;
    rec->consumeTick(tstamp, qty, px);
    cout<<symbol<<" updated "<<rec.get()<<endl;
  }
}

void Engine1::printAscending() const{
  for (auto const & pair: this->lookup){
    cout<<pair.first<<","<<pair.second.get()<<endl;
  }
}