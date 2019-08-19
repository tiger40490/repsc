/*todo: add unit tests
*/
#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;
size_t sz=0;
ostream & operator<<(ostream & os, uint8_t const * x){
  // can't pass array size into operator<<(), so I use a global var
   for(size_t i=0; i<sz; ++i){ 
     unsigned int tmp = x[i];   
     os<<setw(4)<<tmp<<" "; 
   }
   os<<endl;
   return os;
}
template<  template<typename,class> class Container, 
typename V, class Alloc, int min_width=4>
std::ostream& operator<<(std::ostream& os, Container<V, Alloc> const& c){
   // takes any (container or otherwise) template having 2 templ params, but not maps (4) or sets (3)
   for(auto const & it : c){ os<<setw(min_width)<<(unsigned int)it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
void add(uint8_t *A, size_t const lenA,
         uint8_t *B, size_t const lenB){
  assert (lenA >= lenB && "if A is shorter, then user should pass it in as 2nd argument");
  int const offset  = lenA - lenB;
  bool carry=false;
  for (int i=lenA-1; i >=0; --i){
    unsigned int a=A[i], b= (i>=offset)?B[i-offset]:0;
    cout<<i<<" : "<<(int)A[i]<<" + "<<b<<" carry="<<carry<<endl;
    A[i] +=   b+carry;
    carry =(a+b+carry) > 255;
  }
  cout<<(carry?"1(carry)":"")<<A<<".. is the result ----\n";
}  
void test1(){
  vector<uint8_t> A = {129, 1, 255};
  vector<uint8_t> B = {128, 2, 255};
  cout<<A<<B<<".. are the inputs\n";
  sz = A.size();
  add(A.data(), sz, B.data(), B.size());
  assert ( A == vector<uint8_t>({1,4,254}) );
}  
void test2(){
  vector<uint8_t> A = {5, 129, 0,   255};
  vector<uint8_t> B = {   128, 255, 255};
  cout<<A<<B<<".. are the inputs\n";
  sz = A.size();
  add(A.data(), sz, B.data(), B.size());
  assert ( A == vector<uint8_t>({6,2,0,254}) );
}  
int main(){
  test1();
  test2();
}/*Req: Q:  Given 2 BigBinary numbers which are extremely long (size not mentioned), how would you add the numbers? How would you design the function .. how would you represent the input to be function? Remember, the memory usage should be minimal.

https://bintanvictor.wordpress.com/wp-admin/post.php?post=34037&action=edit has more context
*/
