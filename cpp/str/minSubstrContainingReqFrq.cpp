#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector> 
using namespace std;

template<typename T,             int min_width=8> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
static char const BASE='a';
static size_t TABLE_SZ=26; //26 if all chars are a-z
vector<int> frqTable(string const & t){
  vector<int> tmp(TABLE_SZ, 0); 
  for (auto const c: t) ++tmp[c-BASE];
  return tmp;
}  
inline int const getIdx(char c){
    int const idx = c-BASE;
    assert (0 <= idx && idx < TABLE_SZ && "perhaps BASE needs adjusting");
    return idx;
}
bool operator >=(vector<int> const & a, vector<int> const & b){//O(1)
  if (a.size() != b.size()) return false;
  for (int i=a.size()-1; i>=0; --i){
    if (a[i] < b[i]) return false;
  }
  return true;
}
void chopLeft(size_t & le, string const & s, vector<int> & frq, vector<int> const & reqfrq){
  for(;;++le){
    auto idx = getIdx(s[le]);
    if (reqfrq[ idx ] == 0) continue; //chop
    if (reqfrq[ idx ] == frq[idx]) break;
    --frq[idx];
    assert (frq >= reqfrq);
  }
  //cout<<"chopLeft returning with le = "<<le<<endl;
}
string minWindow(string s, string t) {
  size_t sz=s.size();
  if (t.empty() || s.empty()) return "";
  vector<int> const reqfrq = move(frqTable(t)); //should invoke move ctor or RVO, even without move()
  
  // now build the first usable window
  size_t le=0, ri=0, bestsize=0;
  string clean;
  vector<int> frq(TABLE_SZ, 0); 
  for(;;++ri){
    if (ri == sz)return "";
    auto idx = getIdx(s[ri]);
    if( reqfrq[ idx ] == 0 ) continue;
    ++frq[ idx ];
    if (frq >= reqfrq){ //O(1)
      //cout<<s.substr(le, ri-le+1)<<" <-- first usable substring\n";
      chopLeft(le, s, frq, reqfrq);
      bestsize = ri-le+1;
      clean=move(s.substr(le, bestsize));
      if (bestsize == t.size()){
        cout<<"impossible to improve:)\n";
        return clean;
      }
      cout<<clean<<" <== clean substring\n";
      break;
    }
  }
  ////// We have a usable window, now slide it, never growing it
  for(;ri<sz-1; ){
    auto evicted=s[le]; ++le; ++ri;
    if (auto & cnt = frq[ evicted-BASE ]){
      --cnt;
    }
    //cout<<"after sliding ... "<<s.substr(le, ri-le+1)<<endl;
    
    auto idx = getIdx(s[ri]);
    if( reqfrq[ idx ] == 0) continue;
    ++frq[ idx ];
    //cout<<"After successful decrement+increment :\n"<<frq; 
    if (! ( frq >= reqfrq)) continue; //O(1)
      
    cout<<s.substr(le, ri-le+1)<<" <-- another usable substring\n";
    chopLeft(le, s, frq, reqfrq);
    auto const newsize = ri-le+1;            
    if    (bestsize == newsize) continue;
    assert(bestsize > newsize && "sliding window never growing");
        //we have a shorter newsize:)
    bestsize = newsize;
    clean=move(s.substr(le, bestsize));
    cout<<clean<<" <== clean substring\n";
    if (bestsize == t.size()){
          cout<<"impossible to improve:)\n";
          return clean;
    }
  }  
  return clean;
}
int main(){
  assert(minWindow("bba", "ab")=="ba");
  assert(minWindow("adobecodebanc", "abcda")=="adobecodeba");
  assert(minWindow("ccbabccbabcb", "bbc")=="bcb");
  assert(minWindow("abccabccb", "bbc")=="bccb");
  assert(minWindow("abcabccbabcc", "bbc")=="bcab");
}
/*Req: https://bintanvictor.wordpress.com/2018/07/28/find-min-substring-containing-all-my-chars/
Given a string Haystack and a string T, find the minimum window in Haystack which contains all the characters in T in complexity O(n).
*/