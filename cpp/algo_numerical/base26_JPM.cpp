/* 
showcase: strlen, strcmp, c-string manipulation
showcase passing a buffer to be initialized. This technique is fairly 
stanard and described in P124 [[Understanding And Using C Pointers]].
In fact, strcpy() does something similar.

showcase: char const*const   is standard declaration
*/
#include <assert.h>
#include <stdio.h>  
#include <string.h>
using namespace std;

/* param ordinal starts at 1, not zero
returns a pointer into the same buffer "buf". If we only populated the last 3 char in the buffer, then the return value is the address 3 chars before the null character.
*/
char const * convertToBase26(size_t const ordinal, char * const buf, char const*const expectedOutput) {
  size_t const bufSz = strlen(buf);
  assert(bufSz >= 8 && ordinal > 0 && "input requriement");
  char * lastWrite = buf + bufSz; //lastWrite initially positioned at the null character. Must decrement before writing to *lastWrite
  for (size_t cur=ordinal; cur;){
    size_t quotient = cur/26, remainder = cur%26;
    if (remainder == 0){
      remainder = 26;
      assert(quotient>0 && "quotient==remainder==0 would imply cur==0");
      --quotient;
    }
    assert (buf < lastWrite && "buffer size too small for the user input value. The impending write would write outside the buffer and may cause crash");
    *(--lastWrite) = 'a' + remainder - 1;
    cur = quotient; // exit when quotient become zero
  }
  if (expectedOutput){
    assert(strcmp(lastWrite, expectedOutput) == 0);
    printf("%s\t~~ %d as expectedOutput\n", lastWrite, ordinal);
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
  
  for(int i = 1; i< 999; ++i){ //dump part of the infinite sequence
  // the last digit in a column are identical :)
  // the 2nd last digit in a column are a-z
  // the 3rd last digit in a column are identical-so-far
    printf("%3d %2s ", i, convertToBase26(i, buf, nullptr));
    if (i%26==0) printf("\n");
  }
}
/* Requirement: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41278&action=edit
*/