/*
todo: write an in-place solution
showcase operator-overload-conversion
*/
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map> 
#include <map> 
using namespace std;
typedef size_t Pos; //index into input

vector<string> const input{"abc", "xyz", "bac" , "zyx" , "msrd", "acb", "fdsa", "cba", "hlo", "rsdm"}; // Treated as read-only

class TinyHolder4str{
  string const * const addr;
public: 
  TinyHolder4str(string const * a): addr(a){}
  operator string const&() const{ //last const required 
    return *addr; 
  }
  operator char   const*() const{ //last const required 
    return addr->c_str(); // This OOC is very handy for any string-wrapper
  }
};

void produceNew(vector<string> const & input, deque<TinyHolder4str> & output){
  unordered_multimap<string, Pos> table;
  for(Pos i=0; i<input.size(); ++i){
    string tmp = input[i];
    sort(tmp.begin(), tmp.end());
    table.insert({tmp,i});
  }
  for (auto const &it: table){ 
    if ( 1 == table.count(it.first) ) {
      //cout<<it.first<<":"<<input[it.second]<<endl;
      //output.push_back(  TinyHolder4str(it.second)); // testing the by-index ctor        
      output.push_back( TinyHolder4str(&input[it.second])); 
    }else{ // output big anagram groups first
      output.push_front( TinyHolder4str(&input[it.second])); 
    }
  }
  assert (input.size() == output.size());
  for (auto const &s: output) cout<<s<<endl;
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
  deque<TinyHolder4str> output;
  //getanagrams(input);
  produceNew(input, output);
}
/*Req: see email 19 May 2021
Additional req: output the singular strings last.
*/