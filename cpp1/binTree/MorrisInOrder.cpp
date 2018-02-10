/* no recursion no stack, only extra storate for 2 extra pointers!
 * I think the small code size gives a false impression of simplicity
 */
#include <cstdio>
#include <cstring> //memset
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
struct Node {
    int val;
    Node *le, *ri;
    Node(int x, Node * _le = NULL, Node * _ri = NULL) : val(x), le(_le), ri(_ri) {
		registry.push_back(this);
	}
	static vector<Node*> registry;
};
vector<Node*> Node::registry;
/*    5
    4   6
  2       8
 1 3     7 9
https://en.wikipedia.org/wiki/Threaded_binary_tree#Non_recursive_Inorder_traversal_for_a_Threaded_Binary_Tree
*/
    Node _1(-1);
    Node _3(-3);
    Node _2(-2, &_1, &_3);
    Node _4(-4, &_2);
    Node _7(-7);
    Node _9(-9);
    Node _8(-8, &_7, &_9);
    Node _6(-6, NULL, &_8);
    Node root(-5, &_4, &_6);
void Morris3pass(Node * const root) { //buggy
	Node *cur = root;
	 /*first pass (arguable trickiest) -- add thread link to each node without a right child.  Until now I don't understand how this little loop works:) Sometimes we keep moving left; sometimes we keep moving right! Cur is like the current suspect. There are tricky rules how to locate the next suspect.
	Once we confirm a suspect is "HLC" i.e. has left-child, we lock down this node and drive the prev pointer to Descend and locate its predecessor. (Predecessor is always in the left sub-tree.)
	Recursion is avoided because when cur is at a lower node we can traverse up using the thread link.	*/
	while (cur) {
		printf("checking %d\n", cur->val);
		if (cur->le == NULL) {
			cur = cur->ri;
			continue;
		}
		Node * const HLC = cur;
		printf("%d (HLC) is temporarily locked down while we Descend to locate its predecessor\n", HLC->val);
		Node * prev = HLC->le; //purpose of prev: create thread link prev->ri=HLC
		for (; (prev->ri && prev->ri != HLC); prev = prev->ri) {}
		printf(". %d (prev) is the predecessor of %d (HLC)..", prev->val, HLC->val);
		printf(" If prev has no right child, then set the right child to HCL\n");
		if (prev->ri == NULL) {
			prev->ri = HLC; //create thread link
			printf(".. %d 's right child set to %d..Now Descend Right\n",
			prev->val, HLC->val);
			cur = HLC->le; // moving right would likely skip the left subtree!
		}else {
			assert(prev->ri == HLC); //thread link already created
			cur = HLC->ri;
		}
	}// 1st while loop to create the thread links. 2nd while loop would locate lowest value then ...
	printf("-------1st pass done: thread links created -------\n");
	for (cur=root; cur->le; cur = cur->le) {}
	printf("-------2nd pass done: left-most node found -------> %d\n", cur->val);
	
	// 3rd pass to print in-order, using the thread links.
	int lastPrinted = cur->val;
	for(;cur->ri != NULL ;cur=cur->ri){
		// if we found a left child, then descend Left all the way.
		if (cur->le && cur->le->val > lastPrinted )
			for (; cur->le; cur = cur->le) {}
		printf("%d\n", cur->val);
		lastPrinted = cur->val;
	} // 3rd pass
	printf("%d\n\n", cur->val);
} //func Morris3pass()
 
string fromat(void* p){
  static size_t const targetLen=3;
  char buf[16];
  size_t written = sprintf(buf, "%p\0", p);
  return string(buf).substr(written-targetLen);
}
void print1(Node *p){
	if (p) printf("[ %d ]", p->val);
}
void SimpleMorris(Node * cur) { //any branch node
 while (cur != NULL) {
    if (cur->le == NULL){//lowest remaining value
        printf("%d\n", cur->val);
        cur = cur->ri;
        continue;
    }
    // Now cur is not the lowest. Now locate predecessor and set prev to the predecessor.
    // To construct a threaded BST, we will need to set prev->ri to cur
    Node * prev=cur->le; //purpose of prev: create/remove thread link prev->ri=cur
    for (; (prev->ri != NULL && prev->ri != cur); prev = prev->ri) {}

    printf("\t\t\t%d is predecessor of %d\n", prev->val, cur->val);

    assert(cur->le != NULL);
    if (prev->ri == NULL) {
        prev->ri = cur; //create thread link
        printf(" %d 's NULL right child set to %d\n", prev->val, cur->val);

        // not ready to print cur, because cur has left child.
        cur = cur->le;
        prev = NULL; // optionally nullify prev as it is invalidated
    }else{
        //prev->ri = NULL; //optionally remove threadlink
        printf("%d \n", cur->val);

        //after printing cur, no need to move left. Must move right!
        cur = cur->ri;
        //prev = NULL; // optionally nullify prev as it is invalidated
    }
 }//while
}// func SimpleMorris()
void dump(){
 cout<<"---- all the nodes in registry ----\n";
 for (auto n: Node::registry){
    cout<<fromat(n)<<" : "<<fromat(n->le);
	print1(n->le);
	cout<<"\t<= "<< n->val <<" => ";
	print1(n->ri);
	cout<<fromat(n->ri)<<endl;
 }
}
int main() { 
 dump();
 SimpleMorris(&root); 
 dump();
}
