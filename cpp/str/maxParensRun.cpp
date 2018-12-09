/* showcase type alias
   showcase array initialization with zeros

100% pass at Leetcode
*/
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;
using Pos = int;
using Score = size_t;

Score solutionS(std::string const & str){
  size_t const sz = str.size();
  if (sz<=1) return 0;  
  Score ret=0;
  stack<Pos> st; 
  Score closerScore[sz]={0};
  for (Pos i=0; i< sz; ++i){
    char const c = str[i];
    if (c=='('){
      st.push(i);
      continue;
    }
    assert(c==')');
    if (st.empty()) continue;
    
    Pos const opener = st.top();
    st.pop();
    int score = i-opener+1; //use int to check sign
    assert(score >= 2);        
    
    if (opener != 0) 
      if (Score const predecessorScore = closerScore[opener-1])
        score += predecessorScore;
    closerScore[i] = score;
    if ( score > ret) ret = score;
  }
  cout<<"returning "<<ret<<endl;
  return ret;
}
int main(){
  assert( 0 == solutionS("") );
  assert( 0 == solutionS(")") );
  assert( 2 == solutionS("()") );
  assert( 4 == solutionS(")()())") );
  assert( 16 == solutionS(")(())(()()(())())") );
  assert( 16 == solutionS(")(())(()())(())()))") );
}/*Req: https://bintanvictor.wordpress.com/2018/07/22/longest-parentheses-run/
Given a string containing nothing but the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
*/
