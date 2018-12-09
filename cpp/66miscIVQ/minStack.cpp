//no need to be so perfect
#include <stack>
#include <iostream>
using namespace std;
using data=int;
struct Sol{
  void show(){
    cout<<st.size()*100 + pyramid.size()<<" = sizes;\t";
    cout<<"minimum = "<<pyramid.top();
    cout<<";\ttop of stack = "<<st.top()<<endl;
  }
  data push(data in){
    st.push(in);
    if (pyramid.empty() || in <= pyramid.top()){ //equal !
      pyramid.push(in);
    }
    show();
    return pyramid.top();
  }
  data pop(){
    if (st.size() == 0) return -1; 
    auto ret = st.top();
    st.pop();
    if (ret == pyramid.top()){
      pyramid.pop();
    }
    show();
    return ret;
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
  test1();
}/*req: ...

*/