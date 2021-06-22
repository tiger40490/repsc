/* showcase: strlen, strcmp, c-string manipulation
*/
#include <assert.h>
#include <stdio.h>  
#include <string.h>
using namespace std;

// ordinal starts at 1, not zero
char const * convertToBase26(size_t const ordinal, char * buf, char const * expected) {
  size_t const bufSz = strlen(buf);
  assert(bufSz >= 8);
  char * lastWrite = buf + bufSz;
  for (size_t cur=ordinal; cur;){
    int quotient = cur/26, remainder = cur%26;
    if (remainder == 0){
      remainder = 26;
      --quotient;
    }
    *(--lastWrite) = 'a' + remainder - 1;
    cur = quotient; // exit when quotient and cur become zero, 
  }
  if (expected){
    assert(strcmp(lastWrite, expected) == 0);
    printf("%s\t~~ %d as expected\n", lastWrite, ordinal);
  }
  return lastWrite;
}

int main(){
  char buf[] = "12345678"; //strlen = 8
  convertToBase26(1, buf, "a");
  convertToBase26(26, buf, "z");
  convertToBase26(27, buf, "aa");
  convertToBase26(26*3+26, buf, "cz");
  convertToBase26(26*26+26, buf, "zz");
  convertToBase26(2*26*26 + 26*26 +3, buf, "bzc");
  convertToBase26(3*26*26 + 1*26 +1, buf, "caa");
  convertToBase26(3*26*26 + 5*26 +24, buf, "cex");
  
  for(int i = 1; i< 999; ++i){ //dump part of the sequence
  // the last digit in a column are identical :)
  // the 2nd last digit in a column are a-z
  // the 3rd last digit in a column are identical-so-far
    printf("%3d %2s ", i, convertToBase26(i, buf, nullptr));
    if (i%26==0) printf("\n");
  }
}
/* Requirement: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41278&action=edit
*/