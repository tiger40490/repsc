# For re-construction, see https://github.com/tiger40490/repo1/blob/cpp1/cpp/binTree/serialize_deser.cpp
class Node(object):
    def __init__(self, data, left_node=None, right_node=None):
        self.data = data
        self.le = left_node
        self.ri = right_node
'''   5
  2       7
 1 a        8
             9
'''
_9=Node(9)
_8=Node(8, None, _9)
_7=Node(7, None, _8)
_a=Node(3)
_1=Node(1)
_2=Node(2, _1, _a)
_5=Node(5, _2, _7) 
root = _5
marker=Node(None) # should be a special value like None
### above is reusable set-up, and happens to be a BST

class Q: #simple class
    def __init__(self):
        self.list = [] # faster than list()
    def enq(self, item):
        self.list.insert(0,item)
        #print 'pushed', item.data
    def deq(self): return self.list.pop() # throws error if empty

def idd(node):
    return '_' if node is None else ('@%03d' % (id(node)%1000))

def bftWithLevel():
    q = Q()
    q.enq(marker)
    q.enq(root)
    level=0
    while(1):
        node = q.deq()
        if node is marker:
            if not q.list: break;
            level += 1
            print '\nlevel =', level, "\t",
            q.enq(marker)
            continue
        print '%s(%s<-%d->%s)  ' % (idd(node),idd(node.le),node.data,idd(node.ri)),
        if (node.le): q.enq(node.le)
        if (node.ri): q.enq(node.ri)

def visit(node):
    if node is None: return
    if node.le: visit(node.le)
    print node.data
    if node.ri: visit(node.ri)
        
def inOrderDftRecursive():
    visit(root)
    
def main():
    inOrderDftRecursive()

main()
