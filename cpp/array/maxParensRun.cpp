/*
for each index
  if opener
    push the index 
    continue;
  If a closer:
    if stack empty: 
      leave the default score of 0 in the array
      continue
    pop 
    compute the pair score (min 2)
    loop:
      check if there is a score at the position right before the opener, then add that score.
      if zero score there, then exit loop

    Now we have a score for the closer. save it in the closing_scores array
    update max_so_far if needed
end
*/
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;
using Pos = int;
using Score = size_t;

Score solutionS(std::string const & str){
  Score ret=0;
  stack<Pos> st; 
  size_t sz = str.size();
  Score scores[sz]={0};
  for (Pos i=0; i< sz; ++i){
    char const c = str[i];
    if (c=='('){
      st.push(i);
      continue;
    }
    assert(c==')');
    if (st.empty()) continue;
    Pos opener = st.top();
    int score = i-opener+1;
    st.pop();
    assert(score >= 2);        
    if (Score tmp=scores[opener-1])
      score += tmp;
    scores[i] = score;
    if ( score > ret) ret = score;
  }
  cout<<"returning "<<ret<<endl;
  return ret;
}
int main(){
  assert( 4 == solutionS(")()())") );
  cout<<"all tests passed:(\n";
}/*Req: https://bintanvictor.wordpress.com/2018/07/22/longest-parentheses-run/
Given a string containing nothing but the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
*/