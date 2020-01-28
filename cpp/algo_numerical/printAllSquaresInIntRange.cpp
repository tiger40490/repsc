#include <iostream>
using namespace std;

int const limit = 100;

int main(){ //O(sqrt(N)) solution
  cout<<"Here are all the squares found within the range [1, "<<limit<<"]: \n";
  for (int r=0, g=0; ; ++r){
    if ( (g += 2*r+1)  > limit) return 0;
    cout<<g<<" ";
  }
}
/*Req (Yihai's GS IV): given a continuous range of integers starting from 1 (passed in as a list or array), output each item that has an integer square root. 

Eg: For input 1 to 100, should print 1,4,9,16,25,,,100
*/