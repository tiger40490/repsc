#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node *le, *ri;
    Node(int x, Node * left = NULL, Node * right = NULL) : data(x), le(left), ri(right){}
}
/*    5
  2       7
 1 a
*/
_7(7),
_a(6),
_1(1),
_2(2, &_1, &_a),
_5(5, &_2, &_7); //root

bool isAscending = true; //first assume this tree is BST
void recur(Node * n){
//static int lastSeen; // I don't know what initial value can safely represent a special value

  //simulate a random but unlucky initial value, which can break us if without isFirstNodeDone
  static int lastSeen = INT_MAX; //simulate a random but unlucky initial value
  static bool isFirstNodeDone=false; //should initialize to false

  if (!n) return;
  if (n->le) recur(n->le);

  // used to be open(Node *):
  if (!isAscending) return; //check before opening any node
  cout<<"opening "<<n->data<<endl; 
  if (!isFirstNodeDone){ isFirstNodeDone = true; 
  }else if (lastSeen > n->data){
        isAscending=false;
        return; //early return to save time
  }
  lastSeen = n->data;

  if (n->ri) recur(n->ri);
}

int main(){
  recur(&_5);
  cout<< (isAscending?"ok":"nok");
}
