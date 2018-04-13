#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

char play(string && s){
	cout<<s<<" -> rvr function\n";
	return 'r';
}
char play(string & s){
	cout<<s<<" -> lvr function\n";
	return 'l';
}
int main(){
  play(string("naturally-occurring-temp"));
  
  string a="moved-unnamed";
  assert('r' == play(move(a))); //calls the rvr version
  
  string b="move-to-NAMED-rvr-var";
  string && namedRvrVar = move(b);
	
  /*calls the lvr version because namedRvrVar has a Location
and is a l-value expression, even though the string object 
is marked as abandoned*/
  assert('l' == play(namedRvrVar)); 
  
  //can't compile: string && convertedF = forward(string("fwd-to-rvr-var"));
}
