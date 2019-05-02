#include <stack>
#include <iostream>
#include <sstream> //getline
using namespace std;

double evalRpn(string expr){
  stringstream ss(expr); 
  int i;
  string op;
  while(! ss.bad()){
    if (ss>> i){
		cout<<i<<" found an int\n";
	}else{
		ss>>op;
		cout<<op<<" found an operator\n";
	}
  }
  return 0;
}

int main(){
  evalRpn("3 1 5 + * 2 /"); //(3*(1+5)-4)/2
}