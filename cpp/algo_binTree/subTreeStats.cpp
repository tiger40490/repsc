#include "binTreeUtil.h" //tree builder
#include <iostream>
#include <unordered_map>
using namespace std;

auto root = Node<>::preOrderBuildTree({{6, 1.1},
{3, 2.2},{1, 4.4},{2,9.9},{5, 5.5},{4, 10}, //left subtree
{9, 3.3},{7, 6.6},{8, 13},{11,7.7},{10,14},{12, 15}}); //right subtree

void postOrder(Node<> * n){
  static unordered_map<Node<>*, size_t> height={{nullptr, 0}}, size={{nullptr, 0}};
  static int lvl=0;
  ++lvl;
  if (n->le){ postOrder(n->le); }
  if (n->ri){ postOrder(n->ri); }
  
  size[n] = 1 + size[n->le] + size[n->ri];
  height[n] = 1 + max(height[n->le], height[n->ri]);
  cout<<n->data<<"\theight= "<<height[n]<<" size= "<<size[n]<<" level= "<<lvl<<endl;
  --lvl;
}
int main(){
    dumpSubTree(root);
    postOrder(root);
}
