/*
todo: parse input text same as in java
showcase local alias via q[using]
showcase map::emplace()
showcase fwd declare a class template...necessary evil
showcase template default type-arg and where explicit is needed
*/
#include <vector>
#include <list>
#include <set>
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
using rcid=string; //row/column identifier
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
   return os;
}
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, set<T> const & c){
   for(auto const & it: c){ os<<setw(min_width)<<it<<" "; }
   return os;
}

template<typename I_TYPE=int, typename O_TYPE=double, size_t maxTokenCnt=10> class Cell; //fwd declaration required by rclookup map

map<rcid, set<rcid>> p2d; //precedent -> all depdendents

//Global singleton holding all Cells (each saved here upon construction). 
map<rcid, Cell<int>* > rclookup; 
inline char idexist(rcid const & id){return rclookup.count(id);} //can rewrite using find()

template<typename I_TYPE, typename O_TYPE, size_t maxTokenCnt> class Cell{
  vector<string> tokenArray;
  rcid const & id;
  O_TYPE concreteValue = NAN; //initialize to not-a-number i.e. pending
  set<rcid> uu; //unconcretized upstream references
  //list<rcid> downstream;
  friend ostream & operator<<(ostream & os, Cell const & c){
    os<<c.id<<" {unresolved refs="<<c.uu<<"; val="<<c.concreteValue<<" }";
    return os;
  }
  friend void ctorTest();
  /*saves tokenArray into a list of strings
    saves upstream references 
    no validation of formula
  */
  Cell(string const & name, string const & expr): id(name){ 
    assert(!idexist(id));
    stringstream ss(expr);
    this->tokenArray.reserve(maxTokenCnt); //preempt reallocation
    for(string token; getline(ss,token,' ');){
      if ('A' <= token[0] && token[0] <= 'Z'){
        //Cell* upstream;
        p2d[token].insert(id);
        if (idexist(token)){
          Cell * upstream = rclookup[token];
          if (isnan(upstream->concreteValue)){
            tokenArray.push_back(token);
            uu.insert(token);
            ss1<<token<<" is a unresolved precedent\n";
          }else{
            ss1<<token<<" is a concretized precedent:)\n";
            tokenArray.push_back(to_string(upstream->concreteValue));
          }
        }else{
          uu.insert(token);
          ss1<<token<<" is a unconstructed precedent\n";
        }
      }else{ //not a reference
         tokenArray.push_back(token);
      }
    }
    this->evalRpn();
    ss1<<*this<<" constructed\n";
    //ss1<<tokenArray.size()<<" <-- tokenArray parsed \n";
  }
public:
  static Cell* makeCell(rcid const & id, string const & expr){
    ss1<<"makeCell at "<<id<<" ...\n";
    Cell* newCell = new Cell(id, expr);
    assert (!idexist(id) );
    rclookup[id] = newCell;    
    return newCell;
  }
  char evalRpn(){
    if (uu.size()) return 0; //0 indicates "not ready"
    assert (tokenArray.size()); // return 0; 
    if (! isnan(this->concreteValue)) return 'd'; 
    
    using stack=vector<O_TYPE>;  
    stack st;
    for(string const & token: tokenArray){  
      I_TYPE num;
      if (sscanf(token.c_str(), "%d", &num)){
         st.push_back(num); 
         continue; //cout<<num<<" found an int\n";
      }; 
      assert(token.size()==1); //cout<<token<<" found an operator\n";
      assert(st.size()>=2);
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
    //cerr<<id<<" stack: "<<st;
    assert(st.size()==1 && "one item left in stack after evalRpn");
    assert(isnan(this->concreteValue) && "concreteValue is set once only");
    concreteValue = st[0];
    ss1<<concreteValue<<" = concreteValue\n";
    return 'c'; //concretized
  }
};
void ctorTest(){
  Cell<>* ptr = Cell<>::makeCell("C2", "A1 1 5 + * 4 - 2 /"); //(3*(1+5)-4)/2

  ptr = Cell<>::makeCell("A1", "3 1 5 + * 6 / 4 - 2 /"); //(3*(1+5)/6-4)/2
  assert(ptr->concreteValue == -0.5);
  
  ptr = Cell<>::makeCell("B4", "3 1 5 + * 4 - 2 /"); //(3*(1+5)-4)/2
  assert(ptr->concreteValue == 7);
  
  Cell<> cell2("X9", "D3 1 A1 + * E6 / B4 - 2 /"); //(3*(1+5)/6-4)/2
  cout<<*rclookup["A1"]<<endl;
  cout<<p2d;
}	
int main(){
  ctorTest();
}