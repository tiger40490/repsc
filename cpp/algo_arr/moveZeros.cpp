/*
*/
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned int idx;
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<"---- ";
   return os;
}
void wrapper(vector<int> a){
   int left = 0, sz=a.size();
   int right = sz -1;
   while(left < right){ 
       if (0==a[left]){ 
         while (0==a[right]) --right; 
         if (left >= right) break;
         swap(a[left], a[right]);
       }
       ++left;
   }
   cout<<"after : \n"<<a;
}
int main(){
  wrapper({0,0,-1,2,0,4,0,0,8,0});
}/*Req (Leetcode 283): push all zeros to end of vector, in-place and stable reshuffle.
*/