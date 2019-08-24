/*
todo: rename ValType to PayloadType for clarity? too long?

showcase: optional param "callback" to dumpSubTree(). I don't know how to specify a default arg for a func ptr param, so I have to provide a new wrapper function instead.
*/
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
    
    //To use this function on a conceptual tree, you first need to conceptually walk in-order to assign node IDs then walk pre-order to produce an input sequence for preOrderBuildTree()
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
template<typename T> //4-param function
void dumpSubTree4(T const * n, void(*callback)(T const*), size_t const indent=4, size_t const depth=0){
  if (n == nullptr) return;
  if (depth==0){
    std::cout<<"\n       ============  v v v v\n";
  }
  dumpSubTree4(n->ri, callback, indent, depth+1);
  if (depth==1) std::cout<<std::endl;
  std::cout<<std::string(indent* depth, ' ')<<std::left<< n->data ;
  if (callback) callback(n);
  std::cout<<std::endl;
  if (depth==1) std::cout<<std::endl;
  dumpSubTree4(n->le, callback, indent, depth+1);
  if (depth==0){
    std::cout<<  "       ============  ^ ^ ^ ^\n";
  }
}
template<typename T>
void dumpSubTree(T const * n){
  auto nullFuncPtr = static_cast<void(*)(T const*)> (nullptr);
  dumpSubTree4(n, nullFuncPtr);
}/*Based on P458 [[data structure and other objects using c++]]
Can this function serialize/deserialize a binary tree? I think it can.
*/
