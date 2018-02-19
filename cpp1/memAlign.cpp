#include <stdio.h>
#define PACKED  __attribute__((packed))

struct MyStruct{
  char field1, field2;
  long long field3;
} st;
struct MyStructPacked{
  char field1, field2;
  long long field3;
} PACKED stp;

int main() {
  char array[] = "a";
  long long local1;
  char local2='a'; //, char2='b';
  long long local3;
  printf("%p %p %p are addresses of local3, local2, local1, in reverse of declaration order\n", &local3, &local2, &local1);
  printf("%p %p are addresses of array[0], array[1], declared earliest!\n", &array[0], &array[1]);
  printf("%p %p %p are addresses of struct fields without packing\n", &(st.field1), &(st.field2), &(st.field3));
  printf("%p %p %p are addresses of struct fields packed\n", &(stp.field1), &(stp.field2), &(stp.field3));
}
/* Typical output from x64 :

0x7fff51cc0f28 0x7fff51cc0f37 0x7fff51cc0f38 are addresses of local3, local2, local1, in reverse of declaration order
0x7fff51cc0f40 0x7fff51cc0f41 are addresses of array[0], array[1], declared earliest!
0x600b40 0x600b41 0x600b48 are addresses of struct fields without packing
0x600b50 0x600b51 0x600b52 are addresses of struct fields packed
*/
