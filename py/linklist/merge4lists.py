class Node(object):
    def __init__(self, data, next_node=None):
        self.data = data
        self.next = next_node
_8 = Node(8)
_7 = Node(7)
_6 = Node(6)
_5 = Node(5)
_4 = Node(4, _7)
_3 = Node(3, _8)
_2 = Node(2, _5)
_1 = Node(1, _6)
rootA = _1
rootB = _2
rootC = _3
rootD = _4
def dump(node):
  last=0
  while(1):
    if node is None:
      print 'end'
      break
    print node.data, '->',
    assert node.data >= last; last=node.data
    node = node.next
def merge2(A, B):
  return A
def sol2(): # merge 2 lists
  merge2(rootA,rootB)
  merge2(rootA,rootC)
  merge2(rootA,rootD)
  return rootA
def main():
  dump(sol2())
main()
#Req:  https://bintanvictor.wordpress.com/2018/07/08/merge-3-sorted-linked-list/