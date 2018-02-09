#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
int const N = 4; // print a 4x4 matrix
typedef vector<vector<int>> Mat;
Mat seed1 = {{1}};
Mat seed2 = {{4,3},{2,1}};
vector<Mat> all={Mat(), seed1, seed2};

void dump(int const n){
  assert (n > 0 && "bad input");
  Mat arr = all[n];
  for(int row=0; row<n; ++row){
   for(int col=0; col<n; ++col) cout<<arr[row][col]<<"\t";
   cout<<endl;
  }
}


int main(){
	dump(2);
}
/*Requirement: https://wp.me/p74oew-4ae
*/