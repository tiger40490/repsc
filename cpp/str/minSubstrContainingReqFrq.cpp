//showcase concise, empty for-loop
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
static char const aa='a';
static size_t tableSz=3; //26 if all chars are a-z
vector<int> frqTable(string const & t){
  vector<int> tmp(tableSz, 0); 
  for (auto const c: t) ++tmp[c-aa];
  //cout<<"required frq : \n"<<tmp;
  return tmp;
}  
void truncate(size_t & le, string const & s, vector<int> const & reqfrq){
  for(;reqfrq[ s[le]-aa ] == 0;++le); // empty for-loop
  //cout<<"truncate returning with le = "<<le<<endl;
}
bool operator >=(vector<int> const & a, vector<int> const & b){//O(1)
  if (a.size() != b.size()) return false;
  for (int i=a.size()-1; i>=0; --i){
    if (a[i] < b[i]) return false;
  }
  return true;
}
string minWindow(string s, string t) {
  size_t sz=s.size();
  if (t.empty() || s.empty()) return "";
  vector<int> const reqfrq = move(frqTable(t)); //should invoke move ctor or RVO
  
  // now build the first usable window
  size_t le=0, ri=0, bestsize=0;
  string clean;
  vector<int> frq(tableSz, 0); 
  for(;;++ri){
    if (ri == sz){
      cout<<"failed\n";
      return "";
    }
    auto idx = s[ri]-aa;
    if( reqfrq[ idx ] == 0 ) continue;
    ++frq[ idx ];
    //cout<<"incremeting "<<s[ri]<<endl<<frq;
    if (frq >= reqfrq){ //O(1)
      //cout<<s.substr(le, ri-le+1)<<" <-- first good substring\n";
      truncate(le, s, reqfrq);
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
  ////// We have a good window, now slide/truncae it, never growing it
  for(; ri<sz; ){
    auto evicted=s[le]; ++le; ++ri;
    if (auto & cnt = frq[ evicted-aa ]){
      --cnt;
    }
    cout<<"after sliding ... "<<s.substr(le, ri-le+1)<<endl;
    
    //increment on ri
    auto idx = s[ri]-aa;
    if( reqfrq[ idx ] ){
      ++frq[ idx ];
      if (frq >= reqfrq){ //O(1)
        cout<<s.substr(le, ri-le+1)<<" <-- another good substring\n";
        // truncate on left after moving le
        truncate(le, s, reqfrq);
        
        assert(bestsize >= ri-le+1 && "sliding window never growing");
        if    (bestsize == ri-le+1) continue;
        //we have a shorter window!
        bestsize=ri-le+1;
        clean=move(s.substr(le, bestsize));
        cout<<clean<<" <== clean substring\n";
        if (bestsize == t.size()){
          cout<<"impossible to improve:)\n";
          return clean;
        }
      }
      cout<<"After successful decrement+increment :\n"<<frq; 
    }
  }  
  return clean;
}
int main(){
  assert(minWindow("ccbabccbabcb", "bbc")=="bcb");
  assert(minWindow("abccabccb", "bbc")=="bccb");
  assert(minWindow("abcabccbabcc", "bbc")=="bcab");
}
/*Req: https://bintanvictor.wordpress.com/2018/07/28/find-min-substring-containing-all-my-chars/
Given a string Haystack and a string T, find the minimum window in Haystack which contains all the characters in T in complexity O(n).
*/