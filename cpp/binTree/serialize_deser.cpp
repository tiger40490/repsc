//showcase: parsing a stringstream
//todo: how to pass the stringstream object rather than a global variable
//todo: more tests. Might be buggy
#include <queue>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cassert>
#define ss if(1>-2)cout
using namespace std;
stringstream strstr;
typedef int Data;
struct Node {
    Data data;
    Node *left, *right;
    Node(int x, Node * _le = NULL, Node * _ri = NULL) : data(x), left(_le), right(_ri) {}
};
ostream & operator<<(ostream & os, Node const & nd){
  os<<"{ ";
  if (nd.left)  os<<nd.left->data<<" <-";
  os<<"\t[ "<<nd.data/*<<" @ "<<&nd*/<<" ] ";
  if (nd.right) os<<"-> "<<nd.right->data<<" ";
  os<<" }\n";  
  return os;
}
/*    5
    4   6
  2       8
 1 3     7 9
https://en.wikipedia.org/wiki/Threaded_binary_tree#Non_recursive_Inorder_traversal_for_a_Threaded_Binary_Tree
*/
    Node _1(1);
    Node _3(3);
    Node _2(2, &_1, &_3);
    Node _4(4, &_2);
    Node _7(7);
    Node _9(9);
    Node _8(8, &_7, &_9);
    Node _6(6, NULL, &_8);
    Node root(5, &_4, &_6);
void dumpNode(Node * n){cout<<*n;}
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
void genericWalk(Node* root, void (*callback)(Node*)){
  BreadthFirstTraversal(root, callback);
}
void serialize1node(Node * n){
  strstr<<n<<","<<n->data<<","<<n->left<<","<<n->right<<",";
}
void reconstruct(stringstream & arg){
    Node * newRoot = NULL;
    map<string, Node*> lookup;
    vector<string> v; v.reserve(4);
    string token;
    for(int i=0; getline(arg,token, ','); ++i){
      v.push_back(token);
      if (i%4 < 3) continue;
      string id=v[0], idLe=v[2], idRi=v[3]; Data d=stoi(v[1]);
      v.clear();
      ss<<id<<" , "<<d<<" , "<<idLe<<" ^ "<<idRi<<"\n";
      if (lookup.count(id)){ lookup[id]->data = d;
      }else{ 
        Node * n = new Node(d);
        lookup[id]=n;
        if (lookup.size() == 1) newRoot = n;
      }
      Node * n = lookup[id];
      if (idLe != "0"){
        if (!lookup.count(idLe))lookup[idLe] = new Node(-1);    
        n->left = lookup[idLe];
      }
      if (idRi != "0" ){
        if (!lookup.count(idRi)) lookup[idRi] = new Node(-1);          
        n->right = lookup[idRi];
      }
    }
    assert(newRoot);
    cout<<"Reconstructed:\n";
    BreadthFirstTraversal(newRoot, dumpNode);
}
int main() {
    genericWalk(&root, dumpNode);
    genericWalk(&root, serialize1node);
    ss<<strstr.str()<<endl;
    reconstruct(strstr);
}

