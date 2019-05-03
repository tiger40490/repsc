#include <vector>
#include <list>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream> //getline
#include <cassert>
using namespace std;
using rcid=string;
template<typename T,             int min_width=8> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}

template<typename I_TYPE, typename O_TYPE=double, size_t maxTokenCnt=22> class Cell{
  vector<string> tokens;
  O_TYPE concreteValue=0;
  list<rcid> uu; //unconcretized upstream references
  list<Cell> downstream;
public:
  Cell(string const & expr){
    stringstream ss(expr);
    string token;
    this->tokens.reserve(maxTokenCnt); //preempt reallocation
    for(; getline(ss,token,' ');){
      tokens.push_back(token);
      if ('A' <= token[0] && token[0] <= 'Z'){
        uu.push_back(token);
      }
    }
    cout<<tokens.size()<<" <-- tokens pushed\n";
  }
  char evalRpn(){
    using stack=vector<O_TYPE>;  
    if (! uu.empty()) return 0;
    stack st;
    I_TYPE num;
    for(string const & token: tokens){  
      //cout<<st;
      if (sscanf(token.c_str(), "%d", &num)){
         st.push_back(num); 
         continue; //cout<<num<<" found an int\n";
      }; 
      assert(token.size()==1); //cout<<token<<" found an operator\n";
      assert(st.size()>1);
      O_TYPE num2=st.back(); st.pop_back();
      O_TYPE num1=st.back(); st.pop_back();
      if      (token[0]=='+'){
        st.push_back(num1 + num2);
      }else if(token[0]=='-'){
        st.push_back(num1 - num2);
      }else if(token[0]=='*'){
        st.push_back(num1 * num2);
      }else if(token[0]=='/'){
        st.push_back(num1 / num2);
      }
    }
    assert(st.size()==1);
    this->concreteValue = st[0];
    cout<<concreteValue;
    return 'c'; //concretized
  }
};
int main(){
  Cell<int> cell("3 1 5 + * 6 / 4 - 2 /"); //(3*(1+5)/6-4)/2
  cell.evalRpn();
}