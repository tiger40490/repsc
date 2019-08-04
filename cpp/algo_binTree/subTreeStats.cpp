#include "binTreeUtil.h" //tree builder
#include <iostream>
#include <unordered_map>
using namespace std;

auto root = Node<>::preOrderBuildTree({{6, 1.1},
{3, 2.2},{1, 4.4},{2,9.9},{5, 5.5},{4, 10}, //left subtree
{9, 3.3},{7, 6.6},{8, 13},{11,7.7},{10,14},{12, 15}}); //right subtree

struct Stat{
  size_t size=0, height=0;
  size_t maxPathSumLe=0, maxPathSumRi=0; //max path sum to any leaf
};

void postOrder(Node<> * n){
  static unordered_map<Node<>*, Stat> stat={{nullptr, Stat()}}; 
  static int lvl=0;
  ++lvl;
  if (n->le){ postOrder(n->le); }
  if (n->ri){ postOrder(n->ri); }
  
  auto & vo = stat[n];
  vo.size   = 1 + stat[n->le].size 
                + stat[n->ri].size;
  vo.height = 1+max(stat[n->le].height, 
                    stat[n->ri].height);
  cout<<n->data<<"\theight= "<<vo.height<<" size= "<<vo.size<<" level= "<<lvl<<endl;
  --lvl;
}
int main(){
    dumpSubTree(root);
    postOrder(root);
}
