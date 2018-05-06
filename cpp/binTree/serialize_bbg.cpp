#include <queue>
#include <vector>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int x, Node * le = NULL, Node * ri = NULL) : data(x), left(le), right(ri) {}
};

void BreadthFirstTraversal(Node* node, void(*callback)(Node*)){
  queue<Node*> q;
  q.push(node); // must be root
  for (; !q.empty(); node=q.front()){
      q.pop();
      if (node->left) q.push(node->left);
      if (node->right)q.push(node->right);
      callback(node);
  }
}
void genericWalk(Node* node, void (*callback)(Node*)){
  BreadthFirstTraversal(node, callback);
}
void serialize1node(Node * n){
  cout<<n<<",   "<<n->data<<"   ,"<<n->left<<','<<n->right<<'|'<<endl;
}
int main() {
    // https://en.wikipedia.org/wiki/Threaded_binary_tree#Non_recursive_Inorder_traversal_for_a_Threaded_Binary_Tree
    // has this tree diagram
    Node _1(1);
    Node _3(3);
    Node _2(2, &_1, &_3);
    Node _4(4, &_2);
    Node _7(7);
    Node _9(9);
    Node _8(8, &_7, &_9);
    Node _6(6, NULL, &_8);
    Node root(5, &_4, &_6);
    genericWalk(&root, serialize1node);
}
