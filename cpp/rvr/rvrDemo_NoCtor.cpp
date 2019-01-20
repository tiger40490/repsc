#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

char play(string && s){
	cout<<s<<"\t-> rvr function\n";
	return 'r';
}
char play(string & s){
	cout<<s<<"\t-> lvr function\n";
	return 'l';
}
//char play(string s); //competes with the lvr overload and breaks compiler because of ambiguity
int main(){
  assert('r' == play(string("naturally-occurring-temp")));
  
  string a="moved-unnamed";
  assert('r' == play(move(a))); //calls the rvr version cos the move() output is unnamed
  
  string b="move-to-NAMED-rvr-var";
  string && namedRvrVar = move(b);
	
  /*calls the lvr version because namedRvrVar has a Location
and is a l-value expression, even though the string object 
is marked as abandoned*/
  assert('l' == play(namedRvrVar)); 
  
  //can't compile: string && convertedF = forward(string("fwd-to-rvr-var"));
}
