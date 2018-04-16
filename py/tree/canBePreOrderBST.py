class Node(object):
    def __init__(self, data, up_node, left_node=None, right_node=None):
        self.data = data
        self.up = up_node
        self.le = left_node
        self.ri = right_node
        print 'Constructed:', data, (up_node.data if up_node else 'no_uplink')
        
'''   5
  2       7
 1 3    6   8
             9
'''
#root = None

def canBePreOrderBST(li):
  #global root
  root = Node(li[0], None)
  for i in xrange(1, len(li)):
    Node(li[i], None)
  return True

def main():
  assert (canBePreOrderBST([5,2,1,3,7,6,8,9]))
main()