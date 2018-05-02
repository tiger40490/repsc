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
    Node marker(-1); //to be added to queue to mark new level

Node * dequeue(queue<Node*> & q){
    assert(!q.empty());
    Node * n = q.front();
    q.pop();
    return n;
}
void BFT(){
  queue<Node *> q;
  size_t height=0;

  for( q.push(&marker), q.push(&root); !q.empty();){
    Node * n = dequeue(q);
    if (n == &marker){
        if (q.empty()){
                cout<<"  ^^^^^^^^^^"<<endl;
                break;
        }
        n = dequeue(q);
        q.push(&marker); //move the marker to end of queue
        cout<<"starting height # "<<++height<<endl; 
    } 
    int dataL = 0, dataR=0; 
    if (n->left){
        cout<<"pushing "<<n->left->data<<endl; q.push(n->left);
        dataL = n->left->data;
    }
    if (n->right){
        cout<<"pushing "<<n->right->data<<endl; 
        q.push(n->right);
        dataR = n->right->data;
    }
    cout<<dataL<<" <- "<<n->data<<" -> "<<dataR<<endl;// "  #  next is "<<dataN<<endl;
  }
}
int main() {
    BFT();
}
