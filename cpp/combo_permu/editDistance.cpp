//todo: generate from longest to shortest

#define DEBUG
#include "abbr_ascendRecursive.h"
using namespace std;

int main() {
  string small = "abcd";
  outer<deque<char> > ret = generateAsc(small);
}/*Req:
*/