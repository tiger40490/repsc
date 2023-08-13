/*
showcase vector.back() , which equals the last emenet added
*/

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
int main(){
  int const element1 = 1;
  std::vector<int> v{element1,2,3,4,5};
  assert(v.capacity() == v.size() && "initial capacity should equal initilizer list length");
  
  for (int i=v.back(); i<99; ++i){
  	  size_t capB4=v.capacity();
	  auto it = v.begin();
	  cout<<i<<endl;
	  v.push_back(i);
	  if (capB4+1 == v.size()){
		  cout<<*it<<"=itr, capacityB4="<<capB4<<endl;
	  }else{
		  assert(element1 == *it && "without reallocation, iterator should remain valid");
	  }
  }
}