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

template<typename IN, typename OUT=double> class Cell{
  using stack=vector<IN>;
  vector<string> tokens;
  OUT concreteValue=0;
  list<rcid> uu; //unconcretized upstream references
  list<Cell> downstream;
public:
  Cell(string const & expr){
    stringstream ss(expr);
    string token;
    for(; getline(ss,token,' ');){
      tokens.push_back(token);
    }
    cout<<tokens.size()<<" <-- tokens pushed\n";
  }
  void evalRpn(){
    assert(uu.empty());
    stack st;
    IN num;
    for(string const & token: tokens){  
      //cout<<st;
      if (sscanf(token.c_str(), "%d", &num)){
         st.push_back(num); 
         continue; //cout<<num<<" found an int\n";
      }; 
      assert(token.size()==1); //cout<<token<<" found an operator\n";
      assert(st.size()>1);
      IN num2=st.back(); st.pop_back();
      IN num1=st.back(); st.pop_back();
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
  }
};
int main(){
  Cell<int> cell("3 1 5 + * 4 - 2 /"); //(3*(1+5)-4)/2
  cell.evalRpn();
}