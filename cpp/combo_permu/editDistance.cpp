#include "abbr_ascendRecursive.h"
//#define DEBUG

int main() {
  string small = "abcd";
  //deque<char> v(small.begin(), small.end());
  deque<deque<char> > ret = generate(small);
  show(ret);
}/*Req:
*/