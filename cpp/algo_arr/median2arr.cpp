#include <algorithm>
#include <vector>
#include <cassert>
//
// Showcase non-dummy-type template param min_width.
// Note body of map ^ vector dumpers are identical, except some optional features.
// Below is minimum code block for copy-paste.
#include <iostream>
#include <iomanip>
#define Map unordered_map
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

template<typename T,             int min_width=8> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
double medianOf2presorted(vector<double> & xx, vector<double> & yy){
  sort(xx.begin(), xx.end());
  sort(yy.begin(), yy.end());
  ss<<yy;
}
int main(){
  vector<double> xx={3.1, 5, 2, 9};
  vector<double> yy={1,4,3,7,6};
  assert(4 ==  medianOf2presorted(xx,yy));
}/*Req: median of 2 sorted lists

*/
