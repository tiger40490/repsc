#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right, *next;
    Node(int x, Node * le = NULL, Node * ri = NULL) : data(x), left(le), right(ri), next(NULL) {}
};
    Node _15(15);
    Node _14(14);
    Node _13(13);
    Node _12(12);
    Node _11(11);
    Node _10(10);
    Node _9(9);
    Node _8(8);
    Node _7(7, &_14, &_15);
    Node _6(6, NULL, &_13);
    Node _5(5, &_10, NULL);
    Node _4(4, NULL, &_9);
    Node _3(3, &_6,  &_7);
    Node _2(2, &_4,  &_5);
    Node root(1, &_2, &_3);

int maxD=0;
void recur(Node * n){
  static int lvl=0;
  ++lvl;
  if (lvl>maxD) maxD = lvl;
  if (n->left){ recur(n->left); }
  cout<<n->data<<" processed at level = "<<lvl<<endl;
  if (n->right){ recur(n->right); }
  --lvl;
}
int maxDepth(){
    recur(&root);
    cout<<maxD;
}
int main(){
   maxDepth();
}
