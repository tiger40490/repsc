#include <iostream>
using namespace std;

typedef int fn; //a Fib number

/* 0,1,1,2,3,5...
recurs(0,1,0) == 0
recurs(0,1,1) == 1
*/
recurs(fn first, fn second, size_t distance){
	if (distance==0) return first;
	//cout<<first<<","<<second<<","<<distance<<endl;
	return recurs(second, first+second, distance-1);
}

int main(){
  for(int i=0; i<9; ++i)
	cout<<i<<" : "<<recurs(0,1,i)<<endl;
}
