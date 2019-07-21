#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>

template<typename ValType=double>
struct Node {
    typedef int InOrderId;
    ValType const data;
    Node *le, *ri;
    InOrderId const id;
    Node(ValType x, Node*le_=nullptr, 
                    Node*ri_=nullptr, InOrderId id_=-1) 
    : data(x), le(le_), ri(ri_), id(id_) {}
    
    Node(std::pair<InOrderId,ValType> const & arg)
    : Node(arg.second, nullptr, nullptr, arg.first ) {}
    
    //To use this function, you first need to walk in-order to assign node IDs then walk pre-order to produce a sequence for preOrderBuildTree()
    static Node * preOrderBuildTree (std::vector<std::pair<InOrderId,ValType>> const & a){ 
      assert(a.size()); Node * const root = new Node(a[0]);
      for (size_t i = 1; i<a.size(); ++i){
        auto p = root;
        for(auto v=a[i];;){//look for the a parent
          if(v.first <= p->id){
            if(p->le){
              p=p->le; continue; //search for parent
            }
            p->le = new Node(v);
            break;
          }else{
            if(p->ri){
              p=p->ri; continue;
            }
            p->ri = new Node(v);
            break;
          }
        }
        //std::cout<<v.second<<" attached under "<<p->data<<std::endl;
      }
      return root;
    }
};
template<typename T>
void dumpSubTree(T const * n, size_t const indent=4, size_t const depth=0){
  if (n == nullptr) return;
  if (depth==0){
    std::cout<<"\n       ============  v v v v\n";
  }
  dumpSubTree(n->ri, indent, depth+1);
  if (depth==1) std::cout<<std::endl;
  std::cout<<std::string(indent* depth, ' ')<<std::left<< n->data <<std::endl;
  if (depth==1) std::cout<<std::endl;
  dumpSubTree(n->le,  indent, depth+1);
  if (depth==0){
    std::cout<<  "       ============  ^ ^ ^ ^\n";
  }
}/*Based on P458 [[data structure and other objects using c++]]
Can this function serialize/deserialize a binary tree? I think it can.
*/
