/*
showcase comparing 3 numbers
*/
#include "binTreeUtil.h" //tree builder
#include <iostream>
#include <algorithm> //max( {1,2,3} )
#include <unordered_map>
using namespace std;

auto root = Node<>::preOrderBuildTree({{6, 1.1},
{3,-2.2},{1,  -4},{2,0.9},{5, 5.5},{4, -10}, //left subtree
{9, 3.3},{7, 6.6},{8, 13},{11,7.7},{10,14},{12, 15}}); //right subtree

struct SubtreeStat{
  size_t size=0, height=0;
  double maxPathSum=0; /*max path sum from here to 
  any subtree node. non-empty path, so sum can be neg*/
};

typedef int InOrderId;
static unordered_map<InOrderId, SubtreeStat> testing;
void postOrder(Node<> * n){
  static unordered_map<Node<>*, SubtreeStat> stat={{nullptr, SubtreeStat()}}; 
  static int lvl=0;
  ++lvl;
  if (n->le){ postOrder(n->le); }
  if (n->ri){ postOrder(n->ri); }
  
  auto & vo = stat[n];
  vo.size   = 1 + stat[n->le].size 
                + stat[n->ri].size;
  vo.height = 1+max(stat[n->le].height, 
                    stat[n->ri].height);
  vo.maxPathSum = max({stat[n->le].maxPathSum,
                       stat[n->ri].maxPathSum, 0.0}) + n->data;
  cout<<n->data<<"\tmax_path_sum_from_me = "<<vo.maxPathSum<<"  height= "<<vo.height<<" size= "<<vo.size<<" level= "<<lvl<<endl;
  testing[n->id]=vo;
  --lvl;
}
int main(){
    dumpSubTree(root);
    postOrder(root);
    assert(testing[1].maxPathSum==-3.1);
    assert(testing[3].maxPathSum==3.3);
    assert(testing[3].size==5);
    assert(testing[6].size==12); //root
}
