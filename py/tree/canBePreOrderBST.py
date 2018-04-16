class Node(object):
    def __init__(self, data, up_node, left_node=None, right_node=None):
        self.data = data
        self.up = up_node
        self.le = left_node
        self.ri = right_node
        #print 'new', data, (up_node.data if up_node else 'no_uplink')
        
'''   5
  2       7
 1 3    6   8
             9
'''
root = None
def visit(node):
    if node.le: visit(node.le)
    print node.data,
    if node.ri: visit(node.ri)        
def inOrderDftRecursive():
    print '------- dump ------'
    visit(root)
def insertNew(val):
#find the place to insert new node
    parent = root
    while 1:
      if val <= parent.data:
        if parent.le is None: 
          new = Node(val, parent)
          parent.le = new
          return
        parent = parent.le
        continue
      assert(val > parent.data)
      if parent.ri is None:
          new = Node(val, parent)
          parent.ri = new
          return
      parent = parent.ri

def canBePreOrderBST(li):
  global root
  root = Node(li[0], None)
  for i in xrange(1, len(li)):
    insertNew(li[i])
    
  inOrderDftRecursive()
  return True

def main():
  assert (canBePreOrderBST([5,2,1,3,7,6,8,9]))
  
main()