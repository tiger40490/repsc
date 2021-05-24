/*
todo: write an in-place solution
*/
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map> 
#include <map> 
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
//Deepak's solution:
std::vector<std::string> getanagrams( const std::vector<std::string> & sVec  )
{
    std::map<std::string, std::vector<std::string> > mp;   
    std::vector<std::string> result;
    for ( int i = 0; i <sVec.size(); ++i )
    { // each iteration has O(n*log(n) + log(m)), so this loop is O(m*log(m)+mn*log(n))
        std::string item = sVec[i];
        std::string sortedItem = item;
        std::sort( sortedItem.begin(), sortedItem.end() ); //n log(n)
       
        if ( mp.empty() )
        {
            std::vector<std::string> val;
            val.push_back( item );
            mp.insert( std::make_pair( sortedItem, val ) );
        }
        else
        {
            auto itr = mp.find( sortedItem ); //log(m)
            if ( itr != mp.end() )
            {
                itr->second.push_back( item );
            }
            else
            {
              std::vector<std::string> val;
              val.push_back(item);
              mp.insert( std::make_pair( sortedItem, val ) ); //log(m)
            }
       }
    }
   
    for ( auto i = mp.begin(); i!= mp.end(); ++i )
    { // This loop has O(m) i.e. linear time complexity 
        std::vector<std::string> val = i->second;
        for ( auto j = val.begin();  j != val.end(); ++j  )
        {
            result.push_back( *j );
        }
    }
    for (auto const & s: result) cout<<s<<endl;
    return result;    
}

int main(){
  vector<string> output;
  //getanagrams(input);
  produceNew(input, output);
}
/*Req: see email 19 May 2021
*/