import sys
from pprint import pprint
class Node(object):
  def __init__(self, data, next=None):
    self.data = data
    self.next = next
  def pr(self): # shorthand 
    print self
  def __repr__(self):
    nx = self.next
    return '[' + str( self.data ) + '] => ' + str(id(nx) if nx else 0)
_7 = Node(7)
_6 = Node(6, _7)
_5 = Node(5, _6)
_4 = Node(4, _5)
_3 = Node(3, _4)
_2 = Node(2, _3)
_1 = Node(1, _2)
root = _1

def dump(node):
  cnt=0
  while 1:
    if node is None or cnt > 9: break
    cnt+=1
    node.pr()
    node = node.next
print str(_5) ; pprint(_5); sys.exit();
dump(root)
