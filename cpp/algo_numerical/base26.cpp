/* showcase: 
todo: print the first 999 base26 items
*/
#include <assert.h>
#include <stdio.h>  
#include <string.h>
using namespace std;

// ord starts at 1, not zero
char const * convertToBase26(size_t const ord, char * buf, char const * expected) {
  size_t const bufSz = strlen(buf);
  assert(bufSz >= 8);
  char * ret = buf + bufSz-1;
  for (size_t cur=ord;;){
    int quo = cur/26, rem = cur%26;
    if (rem == 0){
      rem = 26;
      --quo;
    }
    *ret = 'a' + rem - 1;    
    if (quo == 0) break;
    --ret;
    cur = quo;
  }
  if (expected){
    assert(strcmp(ret, expected) == 0);
    printf("%s\t~~ %d as expected\n", ret, ord);
  }
  return ret;
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
  
  for(int i = 1; i< 999; ++i){
    printf("%3d %2s ", i, convertToBase26(i, buf, nullptr));
    if (i%26==0) printf("\n");
  }
}
/* Requirement: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41278&action=edit
*/