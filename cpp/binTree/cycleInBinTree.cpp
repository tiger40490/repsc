/*
todo: set up tests
todo: use hash map
showcase: 
*/
#include <iostream>
#include <vector>
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

vector<int> path;

void preorderDFT(Node * n=&root){
  if (path.end() != find(path.begin(), path.end(), n->data)){
    cout<<n->data<<" <- this node triggered cycle detector\n";
    return;
  }
  path.push_back(n->data);
  ss<<path;
  
  if (n->left) { preorderDFT(n->left); }
  if (n->right){ preorderDFT(n->right); }
  auto popped = path.back();
  path.pop_back();
}
void reset(int u, int v){
}
int test1(Node & parent, Node & newChild, bool isLeft=true){
#define WHICH_CHILD (isLeft? parent.left: parent.right)
  Node * orig = WHICH_CHILD;  
  WHICH_CHILD = &newChild;  
  preorderDFT();
  WHICH_CHILD = orig; //now restore  
#undef WHICH_CHILD
}
int main(){
  test1(_9, _6);
  preorderDFT();
}/* Req:  https://bintanvictor.wordpress.com/wp-admin/post.php?post=18950&action=edit

*/