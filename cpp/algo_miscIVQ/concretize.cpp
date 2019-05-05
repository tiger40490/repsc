/*
todo: more asserts
minor todo: output format
minor todo: simplify

showcase local alias via q[using]
showcase fwd declare a class template...necessary evil
showcase template default type-arg and where explicit is needed
*/
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <iostream>
#include <sstream> //getline
#include <cassert>
#include <math.h> //isnan
#define Map std::map //can be either std::map or std::unordered_map
#define ss1 if(1>30)cout //to mass-disable cout 
#define ss2 if(2>0)cout //to mass-disable cout 
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
   os<<"[ ";
   for(auto const & it: c){ os<<setw(min_width)<<it<<" "; }
   os<<"]  "; return os;
}

template<typename I_TYPE=int, typename O_TYPE=double, size_t maxTokenCnt=20> 
class Cell; //fwd declaration required by rclookup map
/* Four containers ranked by importance */
Map<rcid, Cell<>* > rclookup; //#1 Global singleton holding all Cells
inline char id_preExisting(rcid const & id){return rclookup.count(id);} //can rewrite using find()

Map<rcid, set<rcid>> p2d; //#2 precedent->depdendentS.. a.k.a. data propagation graph
set<rcid> roots; //#3 concretized precedent cells, the start of Breadth-first-traversal
set<rcid> pendingCells; //#4(least important) used to detect cycles

template<typename I_TYPE, typename O_TYPE, size_t maxTokenCnt> class Cell{
  vector<string> tokenArray;
  rcid const id; //can't be a reference as the original string could be on stack!
  O_TYPE concreteValue = NAN; //initialize to not-a-number i.e. pending
  set<rcid> uu; //unconcretized upstream references
  friend char walk_tree();
  friend ostream & operator<<(ostream & os, Cell const & c){
    os<<c.id<<" {refs="<<c.uu<<"; val="<<c.concreteValue<<" }"; return os;
  }
  Cell(string const & name, string const & expr): id(name){ 
    assert(!id_preExisting(id));
    stringstream ss(expr);
    this->tokenArray.reserve(maxTokenCnt); //preempt reallocation
    for(string token; getline(ss,token,' ');){
      if ('A' <= token[0] && token[0] <= 'Z'){
        p2d[token].insert(id);
        if (id_preExisting(token)){
          Cell * precedent = rclookup.at(token);
          if (precedent->isConcretized()){
            roots.insert(token);
            ss1<<token<<" is a concretized precedent:)\n";
            token = to_string(precedent->value());//small, optional optimization
          }else{
            uu.insert(token);
            ss1<<token<<" is a unresolved precedent\n";
          }            
        }else{
          uu.insert(token);
          roots.insert(token);
          ss1<<token<<" is a precedent to be constructed\n";
        }
      }
      tokenArray.push_back(token);          
    }
    assert(isPending());
    this->evalRpn();
    if (uu.size() && roots.erase(id)){
      ss2<<id<<" erased from roots\n";
      assert( isPending());
    }
    ss1<<*this<<" constructed\n";
    assert(tokenArray.size());
    ss1<<tokenArray.size()<<" <-- tokenArray parsed \n";
  }
public:
  static Cell* create(rcid const & id, string const & expr){
    //ss1<<"create() at "<<id<<" ...\n";
    assert (!id_preExisting(id) );
    Cell* newCell = new Cell(id, expr);
    rclookup.emplace(id, newCell);    
    return newCell;
  }
  bool isConcretized(){
    bool ret = ! isnan(value());
    if (ret) assert(uu.empty());
    return ret;
  }
  inline bool isPending(){return !isConcretized(); }
  inline set<rcid> uuClone(){ return uu;   }
  inline O_TYPE value(){ return concreteValue; }
  char evalRpn(){
    if (uu.size()) return 0; //0 indicates "not ready"
    if (isConcretized()) return 'd'; //done
    //ss1<<tokenArray<<" = tokenArray in evalRpn\n";
    assert (tokenArray.size());
    
    using stack=vector<O_TYPE>;  stack st;
    for(string const & token: tokenArray){  
      I_TYPE num;
      if (sscanf(token.c_str(), "%d", &num)){
         st.push_back(num); continue; //cout<<num<<" found an int\n";
      }; 
      if ('A' <= token[0] && token[0] <= 'Z'){
        Cell * cell = rclookup.at(token);
        assert(cell->isConcretized());
        st.push_back(cell->value());
        continue;
      }
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
    concreteValue = st[0];
    //++concreteCellCnt;
    ss1<<*this<<" concretized\n";
    pendingCells.erase(this->id);
    return 'c'; //concretized
  }
};
pair<size_t, size_t> make_tree(){
  size_t cCnt=0, rCnt=0; cin>>cCnt>>rCnt>> std::ws;
  for (char r = 'A'; r< 'A'+rCnt; ++r) for (int c = 1; c<=cCnt; ++c){
      rcid id = string(1,r) + to_string(c);
      string line; getline(cin, line); ss1<<id<<" --cin-> "<<line<<endl;
      if (Cell<>::create(id, line)->isPending() ) pendingCells.insert(id);
  }
  return make_pair(cCnt, rCnt);
}
void dumpTree(string heading=""){
  if (heading.size()) ss2<<"-- "<<heading<<" --\n";
  for (auto pair: rclookup){
    ss1<<*(pair.second)<<endl;
  }
  ss2<<"Tree roots = "<<roots<<endl;
  ss2<<"propogation Tree = "<<p2d;
}
char walk_tree(){//BFT
  dumpTree("before walk_tree");
  list<rcid> Q(roots.begin(), roots.end());
  while(Q.size()){
    rcid const id = Q.front(); Q.pop_front();
    Cell<> * cell = rclookup.at(id);
    if (cell->isConcretized() && p2d.count(id)==0) continue;
    ss1<<id<<" ...updating...\n";
    if ( cell->isPending()){
      for (rcid const & cellRef: cell->uuClone()){
        if (rclookup.at(cellRef)->isConcretized()){ 
          cell->uu.erase(cellRef); 
          ss2<<cellRef<<" (concretized) removed from uu set of "<<*cell<<endl;
        }
      }
      if (cell->uu.size()) continue; //dequeued and not enqueued!
      auto status = cell->evalRpn();
      ss2<<*cell<<" has no more unresolved refs, and evalRpn() just returned "<<status<<"\n";
      if(p2d.count(id)==0)continue; //this id has no downstream
    }else{
      assert(p2d.count(id));
    }      
    for (auto const & dep: p2d.at(id)){ Q.push_back(dep);  }
    ss1<<Q<<"<< is the queue after appending dependends of "<<id<<endl;
  }return 0;
}
void resolve1sheet(){
  auto dim = make_tree();
  auto const cellCnt = dim.first * dim.second;
  walk_tree();
  if (pendingCells.size()){
    cerr<<"Cyclic dependencies found... "<<pendingCells<<"are the unresolved cells forming one or more cycles\n";
    throw string("cycle");
  } 
}
void myTestC(){
  try{
    resolve1sheet();
  }catch(string & str){
    assert(str=="cycle");
    ss2<<"Cycle detected as expected :) \n";
  }
}
void myTest1(){
  resolve1sheet();
  double eps=0.0001;
  assert(abs(rclookup["A1"]->value()-20)<eps);
  assert(abs(rclookup["A2"]->value()-20)<eps);
  assert(abs(rclookup["A3"]->value()-20)<eps);
  assert(abs(rclookup["B1"]->value()-8.6666)<eps);
  assert(abs(rclookup["B2"]->value()-3)<eps);
  assert(abs(rclookup["B3"]->value()-1.5)<eps);
  ss2<<"Final cell numbers check :) \n";
}
int main(int argc, char** argv){
  cout<<"\n----- Use stdin to enter data after sheet width and height -----:\n";
  if (argc > 1) { //my tests
    string arg1(argv[1]);
    if     (arg1 == "myTest1") myTest1();  
    else if(arg1 == "myTestC") myTestC();  
  }
}
#ifdef TEST_CTOR
void ctorTest(){
  Cell<>* ptr = Cell<>::create("C2", "A1 1 5 + * 4 - 2 /"); //(3*(1+5)-4)/2

  ptr = Cell<>::create("A1", "3 1 5 + * 6 / 4 - 2 /"); //(3*(1+5)/6-4)/2
  assert(ptr->value() == -0.5);
  
  ptr = Cell<>::create("B4", "3 1 5 + * 4 - 2 /"); //(3*(1+5)-4)/2
  assert(ptr->value() == 7);
  
  ptr = Cell<>::create("X9", "D3 1 A1 + * E6 / B4 - 2 /"); //(3*(1+5)/6-4)/2
  cout<<*rclookup.at("A1")<<endl;
  cout<<p2d;
}	
#endif