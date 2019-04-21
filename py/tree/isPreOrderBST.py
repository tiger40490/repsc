# showcase: global var not defined? Fine!
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
def visit(node):
    if node.le: visit(node.le)
    print node.data,
    if node.ri: visit(node.ri)        
def inOrderDftRecursive():
    visit(root)
    print '\n^ ^ ^ ^ ^ dump ^ ^ ^ ^ ^'
### above are readonly functions
def insertNewFailed(val):
    #print '---- inserting', val
    parent = root
    while 1:
      if val <= parent.data:
        if parent.ri: return 1 #failure
        if parent.le is None: 
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
def insertFailed(x):
'''if x exceeds any of the (would-be-ancestor) nodes visited, then proceed with the descend
else, before moving left, verify the right-child is null
'''       
def sol1_canBePreOrderBST(li):
  global root
  root = Node(li[0], None)
  for i in xrange(1, len(li)):
    if insertNewFailed(li[i]): 
      print 'Failed to insert         ', li[i], '->',
      return False
  return True
def sol8_geeksForGeeks(li):
    s = [] # all the nodes able to take a right child
    root = -2**32
    for value in li: 
        if value < root : 
          print 'Failed to insert', value
          return False     
        while(len(s) > 0 and s[-1] < value) :
          root = s.pop()
          print s
        s.append(value) 
        print s
    return True
def canBePreOrderBST(li):
  print 'input =', li
  #return sol8_geeksForGeeks(li)
  ret = sol1_canBePreOrderBST(li)
  inOrderDftRecursive()
  return ret;  
def main():
  assert (    canBePreOrderBST([40,30,35,80,100]))
  assert (not canBePreOrderBST([40,30,35,20,80,100]))
  assert (    canBePreOrderBST([1,3,2]))
  assert (    canBePreOrderBST([2,1,3]))
  assert (    canBePreOrderBST([3,2,1,5,4,6]))
  assert (not canBePreOrderBST([1,3,4,2]))
  assert (not canBePreOrderBST([3,4,5,1,2]))
  assert (    canBePreOrderBST([5,2,1,3,7,6,8,9])) # diagram above
  assert (not canBePreOrderBST([77,22,11,44,33,40,37,42,39]))
  assert (    canBePreOrderBST([77,22,11,44,33,40,37,42,41]))  
main()
''' Requirement: https://bintanvictor.wordpress.com/2017/04/13/check-array-can-be-preorder-bst-walk/. 
There probably exists some O(N) solution, but I'm not sure
'''
