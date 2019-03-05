// Popular C interview question but somehow this can bring the machine to its knees
// Doesn't work in windows :(
// showcase
#include<iostream>
#include<map>
#include<vector>
#include<assert.h>
#define ss if(1>0) cout
using namespace std;
typedef int PID; // last 2 digits of a pid

map<PID, PID> parent;

PID p2() { return getpid()%100; }
PID pp2(){ return getppid()%100; }

string const //should trigger RVO
ancestry(){
  //stringstream sst;
  PID tmp = p2();
  parent[p2()] = pp2();
  //ss<<p2()<< " now points to "<<pp2()<<endl;

  vector<string> vec;
  for(PID i=p2();;){
    if (i==1) vec.push_back("expired pid");
    vec.push_back(to_string(static_cast<long long int>(i)));
    //ss<<"push_back "<<i<<endl;
    if (!parent.count(i))  break;
    i=parent[i];
  }
  assert (vec.size()>=2);
  string ret = vec[vec.size()-1];
  for (int i=vec.size()-2; i>=0; --i){
    ret += " -> " + vec[i];
  }
  return ret+"\t";
}
int main(){
  cout<<ancestry()<<" born # should show up once only\n\n";
  for (int seq=1; seq<=2; ++seq){
    int fid = fork();
    ss<<ancestry()<<" after fork() # "<<seq<<" from "<<(fid? p2():pp2())<<(fid? " i.e. myself":"")<<endl;
  }
  cout<<ancestry()<<" terminating\n\n"; // should see 2^3 times
}
