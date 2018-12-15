/*
todo: create some simple test cases 
todo: implement my memoization
todo: use external map to save node->meh
todo: edge case -- if all nodes are negative, then need to find and return the highest node data
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cassert>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

template<typename T,             int min_width=3> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<(*it)->data<<" "; }
   //os<<endl;
   return os;
}
struct Node {
    int data, meh; //maxSumEndingHere, possibly zero
    Node *left, *right;
    void neg(){
      data = - abs(data);
      meh = INT_MIN;  
    }
    Node(int x, Node * le = NULL, Node * ri = NULL) : data(x), meh(INT_MIN), left(le), right(ri) {
      all.push_back(this);
    }
    static vector<Node*> all;
};
vector<Node*> Node::all;
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
    Node _4(-4, &_2);
    Node _7(7, &_20, &_21);
    Node _9(9, &_22, &_23);
    Node _8(-8, &_7, &_9);
    Node _6(6, NULL, &_8);
    Node root(-5, &_4, &_6);
vector<Node*> path;
int best=INT_MIN;
/////// all global vars done
int reset(){
  for (auto n: Node::all){
    n->neg();
    n->data *= -1;
  }
  auto ret = best;
  best=INT_MIN;
  path.clear();
  return ret;
}
pair<int,int> kadane(){ //need to save meh for each node
  int ret = INT_MIN, meh = 0;
  //only last node could be uninitialized?
  
  for (int i = 0; i < path.size(); ++i) {
    //assert(path[i]->meh > INT_MIN);
    //if (path[i]->meh)
    auto val = path[i]->data;  
    meh = meh + val;    
    if (ret < meh) ret = meh; //obvious
    if (meh < 0) meh = 0;
    //ss<<meh<<" = meh; ret = "<<ret<<endl;
  }
  cout << " -} "<<ret<<endl; //" = Maximum contiguous sum\n";
  return {ret, meh};
}

void recur(Node * n=&root){
  path.push_back(n);
  ss<<path;
  auto val = kadane();
  n->meh = val.second;
  best = max(best, val.first);
  
  if (n->left) { recur(n->left); }
  if (n->right){ recur(n->right); }
  //auto popped = path.back();
  path.pop_back();
}

int test(){
  recur();
  ss<<best<<" = max path sum\n";
  return reset();
}
int main(){
  assert(test() == 32);
  assert(test() == 51);
  _9.neg();
  assert(test() == 47);
  root.neg();
  _2.neg();
  _13.data=99;
  assert(test() == 104);
}/* Req: https://wp.me/p74oew-64M   
Note: a path is defined as any sequence of nodes from any starting node to any node in the tree along the parent->child connections. The path must contain at least one node and does not need to go through the root. non-unique nodes. No uplink. No cycle.
*/