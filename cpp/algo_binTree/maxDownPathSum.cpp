/*
todo: use external hashmap to save node->meh
todo: rename to maxDownPathSum.cpp
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cassert>
#define meh max_subarray_ending_here
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
int reset(bool isAllPositive=true){
  for (auto n: Node::all){
    n->neg();
    if (isAllPositive) n->data *= -1;
  }
  auto const ret0 = best;
  best=INT_MIN;
  path.clear();
  ss<<"=============\n";
  return ret0;
}
void recur(Node * n=&root){
  int prevMeh=0;
  if (path.size()){ //before adding new node to path
    prevMeh = path.back()->meh;
    assert(prevMeh > INT_MIN);
    if (prevMeh<0)  {
      //ss<<prevMeh <<" is discarded .. starting afresh subarrayEndingHere\n";
      prevMeh = 0;
    }else{
      //ss<<prevMeh <<" is usable.. growing currentSubarrayEndingHere to..\n";
    }
  }
  path.push_back(n);
  ss<<path<<endl; //we don't bother to compute max subarray sum on the current path!
  n->meh = prevMeh + n->data;
  best = max(best, n->meh);
  
  if (n->left) { recur(n->left); }
  if (n->right){ recur(n->right); }
  //auto popped = path.back();
  path.pop_back();
}

int test(){
  recur();
  cout<<best<<" = max path sum\n";
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

  reset(false); //edge case -- all-negative tree
  assert(test() == -1);
}/* Req: https://wp.me/p74oew-64M   
 non-unique nodes. No uplink. No cycle.
*/