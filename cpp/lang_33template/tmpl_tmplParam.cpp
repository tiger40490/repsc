/*
showcase: using 'list', 'vector' without <>
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
//compiler erros out only when you use this object !
Stack1<string, list<int>> compilerFail;
Stack1<double, list<int>> badInst; // bad instantiation but compiles fine

///////////// Above is a traditional implementation, below implementation uses a tmpl-tmpl-param
template <typename T, template<typename> class Cont> class StackTTP{
  Cont<T> underlying;
public:
  size_t size(){return underlying.size(); }
  void push(const T & val){
    underlying.push_back(val);
  }
  void test(){
    this->push(0);
    this->push(333);
    cout<<this->size()<<endl;
  }
};
//Compiler catches this subtle error even if you don't use this oject :)
//StackTTP<double, list<int>> badInstCaughtAtDefinition;

//StackTTP<double, list> goodInst;
StackTTP<double, vector> goodInst;

int main(){
  //compilerFail.test();
  badInst.test();
  goodInst.test();
}/*illustration of TTP, based on [[c++common knowledge]]
*/