class Node(object):
    def __init__(self, data, up_node, left_node=None, right_node=None):
        self.data = data
        self.up = up_node
        self.le = left_node
        self.ri = right_node
        #print 'new', data, '->', (up_node.data if up_node else 'isRoot')
        
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
    visit(root)
    print '\n^ ^ ^ ^ ^ dump ^ ^ ^ ^ ^'
def insertNewFailed(val):
#find the place to insert new node
    print '---- inserting', val
    parent = root
    while 1:
      if val <= parent.data:
        if parent.le is None: 
          if parent.ri: return val #failure
          new = Node(val, parent)
          parent.le = new
          return 0
        parent = parent.le
        #print 'parent set to', parent.data
        continue
      assert(val > parent.data)
      if parent.ri is None:
        new = Node(val, parent)
        parent.ri = new
        return 0
      parent = parent.ri
      #print 'parent set to', parent.data

def canBePreOrderBST(li):
  ret = _canBePreOrderBST(li)
  inOrderDftRecursive()
  return ret;
  
def _canBePreOrderBST(li):
  global root
  root = Node(li[0], None)
  for i in xrange(1, len(li)):
    if insertNewFailed(li[i]): return False
  return True

def main():
  assert (not canBePreOrderBST([5,2,3,1]))
  assert (canBePreOrderBST([5,2,1,3,7,6,8,9]))
  
main()