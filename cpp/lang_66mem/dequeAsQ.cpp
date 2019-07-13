#include <iostream>
#include <deque>
#include <memory>
using namespace std;
struct Payload{
  int * id = new int(++last);
  shared_ptr<int> id2 = make_shared<int>(last);
  static int last;
  ~Payload(){
    auto temp = *id;
    delete id;  
    cout<<temp<<" deleted in dtor\n";
  }
  Payload(){}
  Payload(Payload const & o): id(new int(*(o.id))){}
  friend ostream & operator<<(ostream & os, Payload const & p){
    os<<*(p.id)<<" = id; id2 = "<<*(p.id2);
    return os;
  }
};
int Payload::last = 0;
int main(){
  deque<Payload> wh;
  for (auto i=0; i<7; ++i){
    wh.push_back(Payload());
    cout<<wh[wh.size()-1] <<" = is the highest Payload in warehouse\n";
  }
  cout<<"------------\n";
  while(wh.size()){
    cout<<wh[0] <<" = is the lowest Payload in warehouse\n";
    wh.pop_front();
  }
}/*
As lowest items get removed (and destroyed), deque[0] now points to the next lowest item
*/
