class Node(object):
    cnt=0
    def __init__(self, data, next_node=None):
        assert data > 0
        Node.cnt+=1
        self.data = data
        self.next = next_node
_8 = Node(8)
_7 = Node(7)
_6 = Node(6)
_5 = Node(5)
_4 = Node(4, _7)
_3 = Node(3, _8)
_2 = Node(2, _5) #5
_1 = Node(1, _6) #6
rootA = _1
rootB = _2
rootC = _3
rootD = _4
def dump(node, isAll=False):
  last=0
  dumpCnt=0
  while(1):
    if node is None:
      print 'end'
      break
    print node.data, '->',
    assert node.data >= last; last=node.data
    node = node.next
    dumpCnt+=1
    assert dumpCnt < 99
  if isAll: 
    assert Node.cnt == dumpCnt
def merge2(A, B): 
  dummy = Node(0.1)
  last = dummy #lastMerged
  while A and B:
    if A.data <= B.data:
      last.next = A
      A = A.next 
    else:
      last.next = B
      B = B.next 
    last = last.next
    #dump(dummy)
  # now add the remaining values
  
  assert A or B
  last.next = A or B
  return dummy.next
def sol2(): # merge 2 lists
  global rootA
  rootA = merge2(rootA,rootB)
  rootA = merge2(rootA,rootC)
  rootA = merge2(rootA,rootD)
  return rootA
def main():
  #dump(merge2(rootA, rootB))
  dump(sol2())
main()
#Req:  https://bintanvictor.wordpress.com/2018/07/08/merge-3-sorted-linked-list/