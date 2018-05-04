#include <iostream>
#include <vector>
#include <list>
#include <assert.h>
using namespace std;
  
typedef int field;
vector<field> v{1,2,3,4,  21,22,23,24,  110,120,130,140,  111,222,333,444};
list<field> li(v.begin(), v.end());
typedef list<field>::iterator Itr;
size_t sz=v.size();
size_t const fields=4;
size_t const objCount = sz/fields;
  
void simpleSolution(){
  if (sz%fields) throw "Bad input sizes";
  for(int personIt=0; personIt < objCount; ++personIt){
    for(int fieldIt=0; fieldIt < fields; ++fieldIt){
        cout<<v[personIt+ objCount*fieldIt]<<" ";
    }
  }
}
 
size_t objFixed=0;
Itr objNextField(Itr it){
  for(int i=0; i< objCount-objFixed; ++i){++it; assert(it != li.end()); }
  //cout<<*it<<"   returned from objNextField\n";
  return it;
}
void inPlaceShuffle(Itr const objField1){
  Itr const nextObjField1 = std::next(objField1); //the next id node. We will move to the left of this node
  auto mover=objNextField(objField1);
  for(int i=1; i<=fields-2; ++i){
    auto tmp=mover;
    mover = objNextField(mover); 
    li.splice(nextObjField1, li, tmp);
  }
  li.splice(nextObjField1, li, mover); //last field of the same object
   
  cout<<"after completing one object:   ";
  for(auto it=objField1; it!=li.end(); ++it)  cout<<*it<<" ";
  cout<<endl;
 
  if (  ++objFixed == objCount-1 ) return; //only need to fix N-1 persons, since the last two persons would be fixed in one go
 
  inPlaceShuffle(nextObjField1);//tail recursion is cleaner than iteration
}
int main(){
  inPlaceShuffle(li.begin());
  for(auto it=li.begin(); it!=li.end(); ++it)  cout<<*it<<" ";
}
