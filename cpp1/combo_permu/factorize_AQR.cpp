//Q: how does this algo automatically avoid duplicates?
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <assert.h>
#define ss if(1>0)cout
using namespace std;
vector<int> otherFactors; /*Invariant -- at any time, the latest recursive call's bigNum 
multiplied by all the numbers in this vector equals the original BigNumber */
template<typename T, int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   if (c.empty()) os<<"----------";
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}

size_t factorize(unsigned int bigNum){
  ss<<"entering with bigNum = "<<bigNum<<" <"<<otherFactors;
  size_t cnt =0;
  for (int factor = otherFactors.empty()? 2:otherFactors.back(); //top of the stack
           factor <= sqrt(bigNum);
           factor++ ) {
    if (bigNum%factor) continue; //skip any fake factor
    unsigned int const x = bigNum/factor;
    { for (auto stackItem : otherFactors) ss << stackItem << " * ";
      ss <<" .. "<< factor << " * " << x << endl; // factor*x == bigNum
      cnt++;
    }// output one formula
     
    //now add current factor to the vector and factorize x
    otherFactors.push_back(factor); cnt += factorize(x);
     
    //now restore the vector and continue scanning for the next factor at the current level
    otherFactors.pop_back();
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
