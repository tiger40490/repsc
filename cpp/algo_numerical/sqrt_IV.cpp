// showcase: setprecision once and for all
#include <iostream>
#include <iomanip>
#include <math.h>
#include <assert.h>
using namespace std;

int main(){
  double const target = 2;
  cout<<setprecision(12); 
  double prevGuess = 0;
  double x = target;
  while(abs(prevGuess-x) >= 0.00000001) {
    prevGuess = x;
    x = (x + (target / x)) / 2;
    assert (x<=prevGuess && "new estimate should be smaller than before");
    //assert (x >= sqrt(target) && "should always be an overestimate, but floating point arithmetic can be lossy");
    cout<<x<<endl;
  }
  cout<<x;
}
/* Requirement (Pimco 2018): compute sqrt 2 (or another integer) by converging trial-n-error
*/