/*
Note PRE-order DFT is the only choice for my design.

Quite a short solution, and presumably O(N) time (but XR said can be better) as every node is visited 3 times?

ECT technique showcase: using a vector as stack, since stack is hard to print
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iomanip>
#include <cassert>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

template<typename T,             int min_width=8> ostream & operator<<(ostream & os, vector<T> const & c){
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
vector<int> path; //the stack
unordered_set<int> pathNodes;
/* returns the (unique by design) payload value of one node in the cycle,
2nd return value is an alert isCycleFound
*/
pair<int, bool> preorderDFT(Node * n=&root){
  //if (n == &root)cout<<"-------------\n";
  if (pathNodes.count(n->data)){
    cout<<n->data<<" <- this node triggered cycle detector\n";
    return {n->data, true}; //true to indicate cycle detected
  }
  path.push_back(n->data);   //O(1)
  pathNodes.insert(n->data); //O(1)
  ss<<path; //std::stack would be hard to print !
  
  if (n->left) { 
    auto ret = preorderDFT(n->left);
    if (ret.second) return ret; 
  }
  if (n->right){ 
    auto ret = preorderDFT(n->right);
    if (ret.second) return ret; 
  }
  auto popped = path.back();
  path.pop_back();         //O(1)
  pathNodes.erase(popped); //O(1)
  return {0, false};
}
int test1(int expected, Node & parent, Node & newChild, bool isLeft=true){
  path.clear();
  pathNodes.clear();
#define WHICH_CHILD (isLeft? parent.left: parent.right)
  Node * const orig = WHICH_CHILD;  
  WHICH_CHILD = &newChild;  
  auto result = preorderDFT();
  WHICH_CHILD = orig; //now restore  
#undef WHICH_CHILD
  assert (expected == result.first);
  if (expected > 0)
    assert (result.second && "isCycleFound alert should be turned on");
}
int main(){
  assert (false == preorderDFT().second && "original tree is cycle-free");  
  test1(0, _3, _6, false); //set right child to _6
  test1(3, _3, _3); //set left child to self
  test1(6, _9, _6); //set left child to _6
  test1(5, _3, root, false); //set right child to root
}/* Req:  https://bintanvictor.wordpress.com/wp-admin/post.php?post=18950&action=edit

*/