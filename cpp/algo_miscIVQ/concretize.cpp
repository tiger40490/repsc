/*
showcase local alias via q[using]
showcase fwd declare a class template
minor todo: ctor should be private
minor todo: if an upstream is already resolved then put its value into my tknArray
*/
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream> //getline
#include <cassert>
#include <math.h> //isnan
#define Map std::map //can be either std::map or std::unordered_map
#define ss1 if(1>0)cout //to mass-disable cout 
using namespace std;
using rcid=string;
template<typename K, typename V> ostream & operator<<(ostream & os, pair<K,V> const & p){
   stringstream tmp2;
   tmp2<<p.first<<":"<<p.second;
   os<<tmp2.str();   
   return os;
}
template<typename K, typename V, int min_width=8> ostream & operator<<(ostream & os,  Map<K,V> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
template<typename T,             int min_width=8> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, list<T> const & c){
   for(auto const & it: c){ os<<setw(min_width)<<it<<" "; }
   //os<<endl;
   return os;
}

template<typename I_TYPE, typename O_TYPE=double, size_t maxTokenCnt=22> class Cell; //fwd declaration required by rclookup map

//Global singleton holding all Cells (each saved here upon construction). 
map<rcid, Cell<int>* > rclookup; 

template<typename I_TYPE, typename O_TYPE, size_t maxTokenCnt> class Cell{
  vector<string> tknArray;
  O_TYPE concreteValue=NAN; //not-a-number
  list<rcid> uu; //unconcretized upstream references
  list<rcid> downstream;
  friend ostream & operator<<(ostream & os, Cell const & c){
    os<<"Cell{ unresolved refs="<<c.uu<<"; downstream cells="<<c.downstream.size()<<"; val="<<c.concreteValue<<" }";
    return os;
  }
public:
  /*saves tknArray into a list of strings
    saves upstream references 
    no validation of formula
  */
  Cell(string const & expr){ 
    stringstream ss(expr);
    this->tknArray.reserve(maxTokenCnt); //preempt reallocation
    for(string token; getline(ss,token,' ');){
      tknArray.push_back(token);
      if ('A' <= token[0] && token[0] <= 'Z'){
        uu.push_back(token);
      }
    }
    cout<<tknArray.size()<<" <-- tknArray pushed\n";
  }
  static void makeCell(rcid name, string const & expr){
    rclookup[name] = new Cell<I_TYPE>(expr);
    //auto itr = rclookup.insert(make_pair(name, new Cell<I_TYPE>(expr)));
    //assert(itr.second);
  }
  char evalRpn(){
    using stack=vector<O_TYPE>;  
    if (! uu.empty()) return 0; //0 indicates "not ready"
    stack st;
    for(string const & token: tknArray){  
      I_TYPE num;
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
    }assert(st.size()==1);
    assert(isnan(this->concreteValue) && "should be NAN initially");
    concreteValue = st[0];
    cout<<concreteValue;
    return 'c'; //concretized
  }
};
int main(){
  //Cell<int>::makeCell("A1", "3 1 5 + * 6 / 4 - 2 /"); //(3*(1+5)/6-4)/2

  Cell<int> cell( "3 1 5 + * 6 / 4 - 2 /"); //(3*(1+5)/6-4)/2
  cell.evalRpn();
  cell = Cell<int>("3 1 A5 + * 6 / A4 - 2 /"); //(3*(1+5)/6-4)/2
  cout<<cell;
}