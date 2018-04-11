#include <map>
#include <unordered_map>
#include <list>
#include <vector>

//showcase non-dummy-type template param min_width
//Below is minimum code block for copy-paste
#include <iostream>
#include <iomanip>
using namespace std;

template<typename K, typename V> ostream & operator<<(ostream & os, pair<K,V> const & p){
   os<<p.first<<":"<<p.second;
   return os;
}
template<typename K, typename V, int min_width=4> ostream & operator<<(ostream & os,  map<K,V> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
template<typename T,             int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
int main(){
  vector<int> li={1,5,2,0};
  map<int, int> tm={{1,11}, {2,22}};
  cout<<li<<tm;
}
