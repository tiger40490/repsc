//todo: generate from longest to shortest

//#define DEBUG
#include "abbr_ascendRecursive.h"

int main() {
  string small = "abcd";
  deque<deque<char> > ret = generateAsc(small);
  show(ret);
}/*Req:
*/