/* showcase: 
todo: print the first 999 base26 items
*/
//#include <math.h>
#include <assert.h>
#include <stdio.h>  
#include <string.h>
using namespace std;

char const * convertToBase26(size_t const idx, char * buf, char const * expected) {
  const size_t ord = idx+1; // ord starts at 1, not zero
  size_t const bufSz = strlen(buf);
  assert(bufSz >= 4);
  char * ret = buf + bufSz-1;
  printf("buf=%s, %s=ret\n", buf, ret);
  for (;;){
    break;
  }
  if (expected){
    assert(strcmp(ret, expected) == 0);
  }
  return ret;
}

int main(){
  char buf[8] = "1234567"; 
  convertToBase26(0, buf, nullptr);
}
/* Requirement: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41278&action=edit
*/