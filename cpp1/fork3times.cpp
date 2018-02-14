// Popular C interview question
//
// showcasing macro "ss"
#include<iostream>
//#include<sstream>
#include<map>
#include<vector>
#include<assert.h>
#define ss if(1>0) cout
using namespace std;
typedef int ID2; // last 2 digits of a pid

map<ID2, ID2> parent;

ID2 p2() { return getpid()%100; }
ID2 pp2(){ return getppid()%100; }

string const //should trigger RVO
ancestry(){
  //stringstream sst;
  parent[p2()] = pp2();
  //ss<<p2()<< " now points to "<<pp2()<<endl;

  vector<string> vec;
  for(ID2 i=p2();;){
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
  cout<<ancestry()<<" born # should show up once only"<<endl;
  int fid;
  fid = fork(); ss<<ancestry()<<" after 1st fork from "<<(fid? p2():pp2())<<endl;
  fid = fork(); ss<<ancestry()<<" after 2nd fork from "<<(fid? p2():pp2())<<endl;
  fid = fork(); ss<<ancestry()<<" after 3rd fork from "<<(fid? p2():pp2())<<endl;
  //usleep(999); //interleaving
  cout<<ancestry()<<" terminating\n\n"; // should see 2^3 times
}
