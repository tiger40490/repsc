/*
showcase: using list, vector without <>
*/
#include <list>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;
template<typename T, class Cont> class Stack1{
  Cont underlying;
public:
  size_t size(){return underlying.size(); }
  void push(const T & val){
    underlying.push_back(val);
  }
  void test(){
    this->push(0);
    cout<<this->size()<<endl;
  }
};
//compiler fails only when you use this object !
Stack1<string, list<int>> compilerFail;
// bad instantiation but compiles fine
Stack1<double, list<int>> badInst;
/////////////
template <typename T, template<typename> class Cont> class StackTTP{
  Cont<T> underlying;
public:
  size_t size(){return underlying.size(); }
  void push(const T & val){
    underlying.push_back(val);
  }
  void test(){
    this->push(0);
    cout<<this->size()<<endl;
  }
};
//Compiler catches this error even if you don't use this oject :)
//StackTTP<double, list<int>> badInstCaughtAtDefinition;
//StackTTP<double, list> goodInst;
//StackTTP<double, vector> goodInst;
StackTTP<double, deque> goodInst;

int main(){
  //compilerFail.test();
  badInst.test();
  goodInst.test();
}/*illustration of TTP, based on [[c++common knowledge]]
*/