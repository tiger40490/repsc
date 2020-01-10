#include "binTreeUtil.h"
#include <iostream>
using namespace std;

auto root = Node<>::preOrderBuildTree({{6, 1.1},
{3,2.2},{1,4.4},{2,9.9},{5,5.5},{4,10}, //left subtree
{9,3.3},{7,6.6},{8,13},{11,7.7},{10,14},{12,15}}); //right subtree

int maxD=0;
void recur(Node<> * n){
  static int lvl=0;
  ++lvl;
  if (lvl>maxD) maxD = lvl;
  if (n->le){ recur(n->le); }
  cout<<n->data<<" processed at level = "<<lvl<<endl;
  if (n->ri){ recur(n->ri); }
  --lvl;
}
int maxDepth(){
    recur(root);
    cout<<maxD;
    dumpSubTree(root, 5);
	return 0;
}
int main(){
   maxDepth();
}
