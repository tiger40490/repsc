//todo: use enable_if or something else to disallow std::string
#include <map>
#include <unordered_map>
#include <list>
#include <vector>
//
// Showcase non-dummy-type template param min_width.
// Note body of map ^ vector dumpers are identical, except some optional features.
// Below is minimum code block for copy-paste.
#include <iostream>
#include <iomanip>
#define Map unordered_map
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

template<typename K, typename V> ostream & operator<<(ostream & os, pair<K,V> const & p){
   stringstream tmp2;
   tmp2<<p.first<<":"<<p.second;
   os<<tmp2.str();   
   return os;
}
template<typename K, typename V, int min_width=8> ostream & operator<<(ostream & os,  Map<K,V> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
template<typename T,             int min_width=8> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
int main(){
  //vector<double> li={3.1, 5,2,9};
  vector<string> li={"dabao", "meimei", "princess"};
  Map<int, int> tm={{1,11}, {2,22}};
  ss<<li<<tm;
}
