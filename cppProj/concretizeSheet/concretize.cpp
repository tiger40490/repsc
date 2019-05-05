/* Compile : 
g++ -std=c++17 concretize.cpp && ./a.exe

If too much output, please set macro LOG_LEVEL to 3

feature: negative values supported
*/
/*Design principle:
I keep the Cell object state dynamically updatable, because Cell::concreteValue has to be updated anyway. When this happens, the Cell::uu must stay consistent with it, otherwise state invariants are lost. Clarity and consistency are my top prioriies in this type of design. (Numerous asserts.)

Global data structures are not updated once constructed. No consistency between them and the Cell objects.

In fact, only p2d needs any dynamic update. I decided not to update it to support a valuable future feature -- change propagation. When any root cell has a new value, entire sheet can be udpated follwing the p2d graph (Cell::uu would be empty).

pendingCells, by definition, is dynamically updated... trivial.

In conclusion, Consistency and invariants are maintained within each Cell object only.
*/
/*
todo: find more efficient algorithms
todo: simplify but also add more asserts

showcase fwd declare a class template...necessary evil
showcase template default type-arg and where explicit is needed
showcase template non-type parameter maxTokenCnt
showcase local alias via q[using]
showcase NaN
*/
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <iostream>
#include <sstream> //getline
#include <cassert>
#include <math.h> //isnan
#define Map std::map //can be either std::map or std::unordered_map
#define Set std::set //can be either std::set or std::unordered_set
#define LOG_LEVEL 1 //the more low-level logging is more verbose
#define ss1 if(1>=LOG_LEVEL)cout //to mass-disable cout 
#define ss2 if(2>=LOG_LEVEL)cout //to mass-disable cout 
#define ss3 if(3==LOG_LEVEL)cout //final output
using namespace std;
using rcid=string; //row/column identifier
template<typename K, typename V> ostream & operator<<(ostream & os, pair<K,V> const & p){
   stringstream tmp2;
   tmp2<<p.first<<">>"<<p.second;
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
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, Set<T> const & c){
   os<<"[ ";
   for(auto const & it: c){ os<<setw(min_width)<<it<<" "; }
   os<<"]  "; return os;
}

template<typename I_TYPE=int, typename O_TYPE=double, size_t maxTokenCnt=20> 
class Cell; //fwd declaration required by rclookup map

/* Four containers ranked by importance */
Map<rcid, Cell<>* > rclookup; //#1 all known cells
inline char id_preExisting(rcid const & id){return rclookup.count(id);} //can rewrite using find()

Map<rcid, Set<rcid>> p2d; //#2 precedent->depdendentS mapping.. a.k.a. data propagation graph. Once constructed, never shrunk
Set<rcid> roots; //#3 concretized precedent cells, the start of Breadth-first-traversal
Set<rcid> pendingCells; //#4(least important) used to reveal cells responsible for cycles
size_t cCnt=0, rCnt=0; 

template<typename I_TYPE, typename O_TYPE, size_t maxTokenCnt> class Cell{
  vector<string> tokenArray;
  rcid const id;
  O_TYPE concreteValue = NAN; //initialize to not-a-number i.e. pending
  Set<rcid> uu; //unconcretized upstream references
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
            ss1<<token<<" is a concretized precedent:)\n";
            roots.insert(token);
            token = to_string(precedent->value());//small, optional optimization
          }else{
            ss1<<token<<" is an unresolved precedent\n";
            uu.insert(token);
          }            
        }else{
          ss1<<token<<" is an unconstructed precedent\n";
          uu.insert(token);
          roots.insert(token);
        }
      }
      tokenArray.push_back(token);          
    }
    assert(isPending());
    evalRpn();
    if (uu.size() && roots.erase(id)){
      ss2<<id<<" erased from roots successfully :)\n";
      assert( isPending() && "must remain unconcretized immediately after erase()");
    }
    rclookup.emplace(id, this);    
    ss1<<*this<<" constructed\n";
    assert(tokenArray.size());
    ss1<<tokenArray.size()<<" <-- tokenArray parsed \n";
  }
public:
  inline static Cell* create(rcid const & id, string const & expr){return new Cell(id, expr);  }
  bool isConcretized(){
    bool ret = ! isnan(value());
    if (ret) assert(uu.empty());
    return ret;
  }
  inline bool isPending(){return !isConcretized(); }
  inline Set<rcid> uuClone(){ return uu;   }
  inline O_TYPE value(){ return concreteValue; }
  inline size_t uuCount(){return uu.size(); }
  inline size_t erase1uu(rcid const & uuRef){return uu.erase(uuRef);  }
  char evalRpn(){
    if (uu.size()) return 0; //0 indicates "not ready"
    if (isConcretized()) return 'd'; //done
    //ss1<<tokenArray<<" = tokenArray in evalRpn\n";
    assert (tokenArray.size());
    
    using stack=vector<O_TYPE>;  stack st;
    //ss1<<tokenArray<<" before building RPN stack\n";
    for(string const & token: tokenArray){  
      I_TYPE num;
      //ss1<<token<<" found in tokenArray\n";
      if (sscanf(token.c_str(), "%d", &num)){
         st.push_back(num); continue; //cout<<num<<" found an int\n";
      }else if ('A' <= token[0] && token[0] <= 'Z'){
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
  cin>>cCnt>>rCnt>> std::ws;
  for (char r='A'; r<'A'+rCnt; ++r) for (int c=1; c<=cCnt; ++c){
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
  ss2<<"graph roots = "<<roots<<endl;
  ss2<<"data propagation graph = "<<p2d;
}
char walk_tree(){//BFT
  dumpTree("before walk_tree");
  list<rcid> Q(roots.begin(), roots.end());
  while(Q.size()){
    rcid const id = Q.front(); Q.pop_front();
    Cell<> * cell = rclookup.at(id);
    if (cell->isConcretized() && p2d.count(id)==0) continue; //no subtree below me
    
    ss1<<id<<" ...updating...\n";
    if ( cell->isPending() ){
      for (rcid const & upstream: cell->uuClone()){
        if ( rclookup.at(upstream)->isConcretized()
          && cell->erase1uu(upstream)){
            ss2<<upstream<<" (recently concretized) removed from uu-list of "<<*cell<<endl;
        }
      }
      if (cell->uuCount()) continue; //dequeued and not enqueued again! Basicaly, current cell has unresolved precedents, so we give up on this cell. BFT from another root cell will eventually revisit this cell.
      
      auto status = cell->evalRpn();
      ss2<<*cell<<" has no more unresolved refs, and evalRpn() just returned "<<status<<"\n";
      if(p2d.count(id)==0)continue; //current cell has no subtree, so follow BFT algo
    }else{
      assert(p2d.count(id));
    }      
    //now enqueue all my direct dependent cells:
    for (auto const & dep: p2d.at(id)){ Q.push_back(dep);  }
    ss1<<Q<<"<< is the queue after appending direct dependends of "<<id<<endl;
  }return 0;
}
void resolve1sheet(){
  auto dim = make_tree();
  walk_tree();
  if (pendingCells.size()){
    cerr<<"Cyclic dependencies found... "<<pendingCells<<"are the unresolved cells forming one or more cycles\n";
    throw string("cycle");
  }
  ss3<<cCnt<<" "<<rCnt<<endl;
  for (char r='A'; r<'A'+rCnt; ++r) for (int c=1; c<=cCnt; ++c){
      rcid id = string(1,r) + to_string(c);  
      ss3<<setprecision(5)<<fixed<<rclookup.at(id)->value()<<endl;
  }
}
void myTestC(){
  try{
    resolve1sheet();
  }catch(string & str){
    assert(str=="cycle");
    ss2<<"Cycle detected as expected :) ";
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
  ss2<<"Final cell numbers checked :) ";
}
void myTest2(){
  resolve1sheet();
  double eps=0.0001;
  assert(abs(rclookup["A1"]->value()-6)<eps);
  assert(abs(rclookup["A2"]->value()-5)<eps);
  assert(abs(rclookup["A3"]->value()-3)<eps);
  assert(abs(rclookup["B1"]->value()-0)<eps);
  assert(abs(rclookup["B2"]->value()+1)<eps);  
  assert(abs(rclookup["B3"]->value()+3)<eps);
  ss2<<"Final cell numbers checked :) ";
}
void myTest3(){
  resolve1sheet();
  double eps=0.0001;
  assert(abs(rclookup["A1"]->value()-10)<eps);
  assert(abs(rclookup["A2"]->value()-12)<eps);
  assert(abs(rclookup["A3"]->value()-15)<eps);
  assert(abs(rclookup["B1"]->value()-16)<eps);
  assert(abs(rclookup["B2"]->value()-18)<eps);  
  assert(abs(rclookup["B3"]->value()-21)<eps);
  ss2<<"Final cell numbers checked :) ";
}

int main(int argc, char** argv){
  ss2<<"----- Use stdin to enter data after sheet width and height -----:\n";
  if (argc > 1) { //my tests
    string arg1(argv[1]);
    ss2<<arg1<<"\n";
    if     (arg1 == "myTest1") myTest1();  
    else if(arg1 == "myTest2") myTest2();  
    else if(arg1 == "myTest3") myTest3();  
    else if(arg1 == "myTestC") myTestC();  
    ss2<<arg1<<" completed\n";    
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