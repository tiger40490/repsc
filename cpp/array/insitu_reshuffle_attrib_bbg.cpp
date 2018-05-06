//showcase vector dump with index, using setw()
//todo: better left-align
#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <assert.h>
using namespace std;

typedef size_t index;
typedef int field; 
vector<field> v{1,2,3,4,  21,22,23,24,  110,120,130,140,  111,222,333,444};
size_t const sz=v.size();
size_t constexpr objCount = 4;
size_t const fields=sz/objCount;

template<typename T,             int min_width=3> ostream & operator<<(ostream & os, vector<T> const & c){
   for(int i=0; i<c.size(); ++i) os<<setw(min_width)<<i<<"-";
   os<<"\n";
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
void simpleSolution(){
  if (sz%fields) throw "Bad input sizes";
  for(int personIt=0; personIt < objCount; ++personIt){
    for(int fieldIt=0; fieldIt < fields; ++fieldIt){
        cout<<v[personIt+ objCount*fieldIt]<<" ";
    }
  }
}
/////////// O(1)-space eviction solution
index convert(index i, field val2mv = -9999){
  //cout<<val2mv<<" is the value at old home = "<<i<<"\n";
  int oid = (i)%objCount; //0 means 1st obj
  int fid = (i)/objCount; //0 means 1st field; 1 means 2nd field
  //cout<<oid<<" = oid; fid = "<<fid<<endl;
  index ret = (oid)*fields + fid;
  //cout<<ret<<" = new home\n";
  assert(ret < sz);
  return ret;
}
void evictionSolution(){ //tested
  size_t mvcnt=0;
  index oldHome=1; field val2mv=v[oldHome ];
  while( mvcnt < sz-2/*move all but 1st/last nodes*/){
        index newHome = convert(oldHome);
        field tmp = v[newHome]; //save
        if (tmp < 0) {
          ++oldHome; val2mv = v[oldHome];
          continue;
        }
        v[newHome] = -val2mv;
        ++mvcnt;
        oldHome = newHome; val2mv = tmp;
        assert (val2mv>0);
  }
  for(auto & e: v) if(e<0) e = -e;
  // for(int i=0; i<sz; ++i) if (v[i]<0) v[i]=-v[i];
}
/////////// solution on a list input (not applicable if input is array):
list<field> li(v.begin(), v.end());
typedef list<field>::iterator Itr;
size_t objFixed=0;
Itr objNextField(Itr it){
  for(int i=0; i< objCount-objFixed; ++i){++it; assert(it != li.end()); }
  //cout<<*it<<"   returned from objNextField\n";
  return it;
}
void inPlaceShuffle(Itr const objField1){ //tested
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
  cout<<"\nbefore evictions, \n"<<v;
  evictionSolution();
  cout<<"after evictions, \n"<<v;
}
