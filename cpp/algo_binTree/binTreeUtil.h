//todo: indent can be a non-type template param
#include <iostream>
#include <iomanip>

struct Node {
    int data;
    Node *le, *ri;
    Node *next; //optional
    Node(int x, Node*le_=nullptr, Node*ri_=nullptr) : data(x), le(le_), ri(ri_), next(NULL) {}
};
template<typename Node>
void dumpSubTree(Node const * n, size_t const indent=4, size_t const depth=0){
  if (n == nullptr) return;
  if (depth==0){
    std::cout<<"\n       ============  v v v v\n";
  }
  dumpSubTree(n->ri, indent, depth+1);
  std::cout<<std::string(indent* depth, ' ')<<std::left<< n->data <<std::endl;
  dumpSubTree(n->le,  indent, depth+1);
  if (depth==0){
    std::cout<<  "       ============  ^ ^ ^ ^\n";
  }
}/*Based on P458 [[data structure and other objects using c++]]
Can this function serialize/deserialize a binary tree? I think it can.
*/
