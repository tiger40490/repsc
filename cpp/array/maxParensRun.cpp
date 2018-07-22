/*for each index:
  if an opener: 
    push the index on the stack 
    continue
  if a closer:
    if stack empty: continue
    pop 
    compute the pair score (min 2)
    update max_so_far if needed
end
*/
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

size_t solutionS(std::string const & str){
  return 0;
}
int main(){
  assert( 4 != solutionS(")()())") );
  cout<<"all tests passed:(\n";
}/*Req: https://bintanvictor.wordpress.com/2018/07/22/longest-parentheses-run/
Given a string containing nothing but the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
*/