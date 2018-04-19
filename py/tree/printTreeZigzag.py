class Node(object):
    def __init__(self, data, left_node=None, right_node=None):
        self.data = data
        self.le = left_node
        self.ri = right_node
'''    1
   3       2
  4 5    6   7
10      9     8
'''
_5=Node(5) 
_8=Node(8)
_9=Node(9)
_10=Node(10)
_6=Node(6, _9)
_7=Node(7, None, _8)
_4=Node(4, _10)
_2=Node(2, _6, _7)
_3=Node(3, _4, _5)
_1=Node(1, _3, _2)
root = _1
marker=Node(None) # should be a special value like None
class Q: #simple class
    def __init__(self):
        self.list = [] # faster than list()
    def enq(self, item):
        self.list.insert(0,item)
        #print 'pushed', item.data
    def deq(self): return self.list.pop() # throws error if empty

def bftWithLevel():
    q = Q()
    st = list()
    q.enq(marker)
    q.enq(root)
    level=0
    while True:
        node = q.deq()
        if node is marker:
            if not q.list: break;
            q.enq(marker)
            level += 1
            print '\nlevel =', level, "\t",
            if level%2:
              for i in reversed(st): print i,
              del st[:]
            continue
        if level%2: 
          print node.data,
        else:
          st.append(node.data)
        if (node.le): q.enq(node.le)
        if (node.ri): q.enq(node.ri)
    for i in reversed(st): print i,
def main():
    bftWithLevel()
main()

'''Requirement: print any tree (you can start with a binary) by level, in zigzag sequence
'''