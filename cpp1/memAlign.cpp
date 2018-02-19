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
  long long local1; //uninitialized
  char local2, local3;
  long long local4;
  printf("%p %p %p %p are addresses of locals, in reverse of declaration order\n", &local4, &local3, &local2, &local1);
  printf("%p %p are addresses of array[0], array[1], declared earliest!\n", &array[0], &array[1]);
  printf("%p %p %p are addresses of struct fields without packing\n", &(st.field1), &(st.field2), &(st.field3));
  printf("%p %p %p are addresses of struct fields packed\n", &(stp.field1), &(stp.field2), &(stp.field3));
}
/* Typical output from x64 :

0x7fff0c15b788 0x7fff0c15b796 0x7fff0c15b797 0x7fff0c15b798 are addresses of locals, in reverse of declaration order
0x7fff0c15b7a0 0x7fff0c15b7a1 are addresses of array[0], array[1], declared earliest!
0x600b50 0x600b51 0x600b58 are addresses of struct fields without packing
0x600b60 0x600b61 0x600b62 are addresses of struct fields packed
*/
