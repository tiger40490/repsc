#include <cstdio>
#include <assert.h>
struct Node {
    int val;
    Node *le, *ri;
    Node(int x, Node * _le = NULL, Node * _ri = NULL) : val(x), le(_le), ri(_ri) {}
};
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
void MorrisTraversal(Node * const root) { //no recursion, no stack, extra storate for 2 extra pointers
 Node *cur = root;
 while (cur != NULL) {
    if (cur->le == NULL) { // cur is the lowest remaining value!
        printf("%d \n", cur->val);
        cur = cur->ri;
        continue;
    }
    // Now cur is not the lowest. Now locate predecessor and set prev to the predecessor.
    // To construct a threaded BST, we will need to set prev->ri to cur
    // ( In a Backward traversal, we would find successor instead. )

    Node * prev=cur->le; //purpose of prev: create/remove thread link prev->ri=cur
    for (; (prev->ri != NULL && prev->ri != cur); prev = prev->ri) {}

    printf("   %d is the predecessor of %d\n", prev->val, cur->val);

    assert(cur->le != NULL);
    if (prev->ri == NULL) {
        prev->ri = cur; //create thread link
        printf(" %d 's right child set to   %d\n", prev->val, cur->val);

        // not ready to print cur, because cur has left child.
        cur = cur->le;
        prev = NULL; // optionally nullify prev as it is invalidated
    }else{
        //prev->ri = NULL; //optionally remove threadlink
        //printf(" %d 's right thread link removed\n", prev->val);
        printf("%d \n", cur->val);

        //after printing cur, no need to move left. Must move right!
        cur = cur->ri;
        prev = NULL; // optionally nullify prev as it is invalidated
    }
 }//while
 printf("\n");
}
int main() { MorrisTraversal(&root); }
