/*
todo:
showcase: default param value is address of tree root node
*/
#include <iostream>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <cassert>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

template<typename T,             int min_width=8> ostream & operator<<(ostream & os, deque<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   //os<<endl;
   //for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}

struct Node {
    int data;
    Node *left, *right, *next;
    Node(int x, Node * le = NULL, Node * ri = NULL) : data(x), left(le), right(ri), next(NULL) {}
};
/*    5
    4    6
   2         8
 1   3     7    9
11 13    20 21 22 23
*/
    Node _20(20);
    Node _21(21);
    Node _22(22);
    Node _23(23);
    Node _11(11);
    Node _13(13);
    Node _1(1, &_11);
    Node _3(3, &_13);
    Node _2(2, &_1, &_3);
    Node _4(4, &_2);
    Node _7(7, &_20, &_21);
    Node _9(9, &_22, &_23);
    Node _8(8, &_7, &_9);
    Node _6(6, NULL, &_8);
    Node root(5, &_4, &_6);

int uu,vv;
deque<int> path, pathU, pathV;

//data structure below helps speed up the algo in the very common scenario where both nodes are on the same path.
deque<int> samePathCheck;
pair<bool, int> samePath; //both nodes are on the same path, i.e. one is a child
void recur(Node * n=&root){
  if (samePath.first) return;
  if (pathU.size() && pathV.size()) return;
  if (path.end() != find(path.begin(), path.end(), n->data)){
    cout<<"cycle\n";
    return;
  }
  path.push_back(n->data);
  ss<<path;
  
  if (n->data == uu){
    //ss<<uu<<" found:)\n";
    samePathCheck.push_back(uu);
    if (samePathCheck.size() == 2){
      samePath.first = true;
      samePath.second = samePathCheck[0];
      return;
    }
    pathU = path;
  }else if (n->data == vv){
    //ss<<vv<<" found:)\n";
    samePathCheck.push_back(vv);
    if (samePathCheck.size() == 2){
      samePath.first = true;
      samePath.second = samePathCheck[0];
      return;
    }
    pathV = path;
  }
  if (n->left) { recur(n->left); }
  if (n->right){ recur(n->right); }
  auto popped = path.back();
  if (vv == popped || popped == uu) {
    assert(popped == samePathCheck.back());
    samePathCheck.pop_back();
  }
  path.pop_back();
}
void reset(int u, int v){
    samePath = pair<bool,int>();
    samePathCheck.clear();
    pathU.clear();
    pathV.clear();
    path.clear();
    uu = u;
    vv = v;
}
int test1(int u, int v){
    if (u == v) return u; //Leetcode guarantees both present
    reset(u,v);
    recur();
    if (samePath.first) {
      ss<<samePath.second<<" <-- discovered as an ancestor of the other target\n";
      return samePath.second;
    }
    //assert(pathV.size() && pathU.size() && "Leetcode said both present");
    ss<<uu<<" in"<<pathU;
    ss<<vv<<" in"<<pathV;
    auto ret = pathU[0];
    for (size_t idx=1; ;++idx){
      if (pathU[idx] != pathV[idx]){ 
        //ss<<ret<<" = ret\n";
        return pathU[idx-1];
      }
    }
}
int main(){
   assert(test1(2,5)==samePath.second  &&  samePath.first);
   assert(test1(4,3)==samePath.second  &&  samePath.first);
   assert(test1(21,6)==samePath.second &&  samePath.first);
   assert(test1(11,6)==5               && !samePath.first);
   assert(test1(13,9)==5               && !samePath.first);
   assert(test1(4,4)==4);
   _20.right = &_8;    // introduce a cycle, not in leetcode scope
   assert(test1(9,7)==8);
   assert(test1(23,7)==8);
   assert(test1(8,9)==samePath.second  &&  samePath.first);
}/* Req: given 2 nodes (and root) of a binary tree, find the lowest common ancestor. A node can be a (direct/indirect) descendant of itself. All distinct values. No uplink. No cycle
*/