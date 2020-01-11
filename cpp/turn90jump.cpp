#include <vector>
#include <cstdlib>
#include<string>
//
// Note body of map ^ vector dumpers are identical, except some optional features.
// Below is minimum code block for copy-paste.
#include <iostream>
#include <iomanip>
#define Map unordered_map
#define Set set
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

unsigned int gcd(int u, int v){
	u = abs(u); v=abs(v);
    return (v != 0) ? gcd(v, u % v) : u;
}

string solution(int ax, int ay, int bx, int by){
	int dy=by-ay, dx=bx-ax;
	//todo: check lucky
	//now, not lucky
	
	//simplfy ratio ,,, actually can find a point closer to B
	size_t tmp=gcd(dy, dx);
	dy /= tmp; 
	dx /= tmp;
	cout<<dy<<"/"<<dx<<" after simplify\n";
	swap(dy,dx);
	dy = -dy;
	cout<<dy<<"/"<<dx<<" after swap and negate\n";
	return to_string(bx+dx) +"," +to_string(by+dy);
}

int main(){
  //cout<<gcd(-2,4)<<endl;
  cout<<solution(-1,3,3,1);
}
