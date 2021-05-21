/*
todo: write an in-place solution
*/
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map> 
using namespace std;

vector<string> input{"abc", "xyz", "bac" , "zyx" , "msrd", "acb", "fdsa", "cba", "hlo", "rsdm"};

void produceNew(vector<string> const & input, vector<string> & output){
  typedef size_t pos; //index into input
  unordered_multimap<string, pos> table;
  for(pos i=0; i<input.size(); ++i){
    string tmp = input[i];
    sort(tmp.begin(), tmp.end());
    table.insert({tmp,i});
  }
  for (auto const &it: table){ // output big anagram groups first
    if ( 1 == table.count(it.first) ) continue;
    cout<<it.first<<":"<<input[it.second]<<endl;
    output.push_back(input[it.second]);
  }
  for (auto const &it: table){ // output singular groups last
    if ( 1 <  table.count(it.first) ) continue;
    cout<<it.first<<":"<<input[it.second]<<endl;
    output.push_back(input[it.second]);
  }
  assert (input.size() == output.size());
}
int main(){
  vector<string> output;
  produceNew(input, output);
}
/*Req: see email 19 May 2021
*/