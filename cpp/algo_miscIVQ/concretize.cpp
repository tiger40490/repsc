/*
showcase local alias via q[using]
showcase map::emplace()
showcase fwd declare a class template...necessary evil
showcase template default type-arg and where explicit is needed
minor todo: add more assertions to aid refactor
minor todo: if an upstream is already resolved then put its Value into my tknArray
minor todo: make Cell constructable on heap only
todo: populate the graph
todo: populate the top-level cells
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
   return os;
}

template<typename I_TYPE=int, typename O_TYPE=double, size_t maxTokenCnt=10> class Cell; //fwd declaration required by rclookup map

//Global singleton holding all Cells (each saved here upon construction). 
map<rcid, Cell<int>* > rclookup; 

template<typename I_TYPE, typename O_TYPE, size_t maxTokenCnt> class Cell{
  vector<string> tknArray;
  O_TYPE concreteValue = NAN; //initialize to not-a-number
  list<rcid> uu; //unconcretized upstream references
  list<Cell<I_TYPE>*> downstream;
  friend ostream & operator<<(ostream & os, Cell const & c){
    os<<"Cell{ unresolved refs="<<c.uu<<"; downstream cells="<<c.downstream.size()<<"; val="<<c.concreteValue<<" }";
    return os;
  }
  friend void testCtor();
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
        Cell* upstream = Cell::makeCell(token, "");
        upstream->downstream.push_back(this);
      }
    }
    ss1<<tknArray.size()<<" <-- tknArray parsed \n";
  }
public:
  static Cell* makeCell(rcid const & cellName, string const & expr){
  //auto itr = rclookup.insert(make_pair(name, new Cell(expr)));
    auto itr = rclookup.emplace(cellName, new Cell(expr));
    return itr.first->second; //arcane 
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
    }assert(st.size()==1 && "one item left in stack after evalRpn");
    assert(isnan(this->concreteValue) && "concreteValue is set once only");
    concreteValue = st[0];
    ss1<<concreteValue<<" = concreteValue\n";
    return 'c'; //concretized
  }
};
void testCtor(){
  Cell<int>* ptr = Cell<int>::makeCell("A1", "3 1 5 + * 6 / 4 - 2 /"); //(3*(1+5)/6-4)/2
  ptr->evalRpn(); assert(ptr->concreteValue == -0.5);
  
  Cell<int> cell( "3 1 5 + * 4 - 2 /"); //(3*(1+5)-4)/2
  cell.evalRpn(); assert(cell.concreteValue == 7);
  
  Cell<int> cell2("3 1 A1 + * 6 / A4 - 2 /"); //(3*(1+5)/6-4)/2
  cout<<cell2<<endl;
  cout<<*rclookup["A1"]<<endl;
}	
int main(){
  testCtor();
}