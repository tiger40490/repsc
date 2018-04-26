#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <assert.h>
#define ss if(1>0)cout
using namespace std;
vector<int> st;
template<typename T, int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   if (c.empty()) os<<"----------";
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}

size_t factorize(unsigned int bigNum){
  ss<<"entering with bigNum = "<<bigNum<<" <"<<st;
  size_t cnt =0;
  for (int factor = st.empty()? 2:st.back(); //top of the stack
           factor <= sqrt(bigNum);
           factor++ ) {
    if (bigNum%factor) continue; //skip any fake factor
    unsigned int const x = bigNum/factor;
    { for (auto stackItem : st) ss << stackItem << " * ";
      ss << factor << " * " << x << endl;
      cnt++;
    }// output one formula
    st.push_back(factor);
    cnt += factorize(x);
    st.pop_back();
  }
  return cnt;
}
int main(){
  assert(8 == factorize(36));
  assert(6 == factorize(24));
  assert(3 == factorize(12));
}
/*Requirement: https://bintanvictor.wordpress.com/2017/04/16/factorize-a-natural-number-aqr/
Solution from my friend Shanyou, using a global vector in recursion?
*/
