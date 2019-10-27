/*
showcase erase multiple items from map, avoiding iterator invalidation. My technique avoids iterator and uses erase-by-key
*/
#include <map>
#include <vector>
#include <iostream>
#include <assert.h>
//#define ss if(2>1) cout
using namespace std;

void populate_map(map<string, int> & entryMap){  //non-const arg, to be populated
  int cnt;
  cin>>cnt;
  cout<<cnt<<"=cnt"<<endl;
  string key; int val;
  for (int i=0; i<cnt; ++i){
	  cin>>key>>val;
	  entryMap[key]=val;
	  cout<<key<<endl;
  }
}

/*Req: erase all entries having pair.second==tgt
*/
template <typename K, typename V> int eraseByVal(map<K,V> m, V tgt){ 
  vector<K> keys; //list is possibly more "natural" but vector is common, and faster with DAM
  for (auto const & p: m){
    if (p.second == tgt) keys.push_back(p.first);
  }
  for (auto const & key: keys) m.erase(key);

  cout<<keys.size()<<" pairs erased, new map size = "<<m.size()<<"\n";
  return keys.size();
}

int main(){
  map<double, int> m({ {15.203, 2}, {793.231,2}, {11.235, 1}, {13.1313,4}, {68.235,3} });
  eraseByVal(m, 2);
  eraseByVal(m, 1);
  eraseByVal(m, 77039870);  
}
