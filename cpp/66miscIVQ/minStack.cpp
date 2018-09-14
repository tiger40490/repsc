//no need to be so perfect
#include <stack>
#include <iostream>
using namespace std;
using data=int;
struct Sol{
  void show(){
    cout<<"minimum = "<<pyramid.top()<<endl;
  }
  data push(data in){
    st.push(in);
    show();
  }
  data pop(){
    show();
  }
private:
  stack<data> st;
  stack<data> pyramid; 
} inst;

void test1(){
  inst.push(5);
  inst.push(33);
  inst.push(22);
  inst.pop();
  inst.push(11);
  inst.pop();
  inst.push(33);
  inst.push(5);
  inst.pop();
  inst.push(55);
  inst.push(5);
  inst.pop();
}
int main(){
  
}/*req: ...

*/