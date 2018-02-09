#include <iostream>
using namespace std;
int const N = 4; // print a 4x4 matrix
int arr[N][N];
void dump(){
  for(int row=0; row<N; ++row){
   for(int col=0; col<N; ++col) cout<<arr[row][col]<<"\t";
   cout<<endl;
  }
}

int main(){
	dump();
}
/*Requirement: https://wp.me/p74oew-4ae
*/