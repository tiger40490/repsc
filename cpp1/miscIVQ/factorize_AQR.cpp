#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <assert.h>
using namespace std;
vector<int> st;
template<typename T, int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}

size_t factorize(unsigned int bigNum){
  cout<<"entering with bigNum = "<<bigNum<<" and"<<st;
  size_t cnt =0;
  for (int factor = st.empty()? 2:st.back(); //top of the stack
           factor <= sqrt(bigNum);
           factor++ ) {
    if (bigNum%factor) continue; //skip any fake factor
    unsigned int const x = bigNum/factor;
    for (int j=0; j<st.size(); j++) cout << st[j] << " * ";
    cout << factor << " * " << x << endl;
    cnt++;
    st.push_back(factor);
    cnt += factorize(x);
    st.pop_back();
  }
  //cout<<"^^^^ "<<cnt<<" formula found so far ^^^^^\bigNum";
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
