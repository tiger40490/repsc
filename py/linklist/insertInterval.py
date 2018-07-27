'''
showcase double linked list
'''
import sys, bisect
A='A' # Above-water 
B='B' # Below-Water
class Node(object): # each node is a segment
    cnt=0
    def __init__(self, leftMark, prev_node=None, color=A):
        assert leftMark > 0
        Node.cnt+=1
        self.leftMark = leftMark # rightMark would be self.next.leftMark-1. I choose not to save rightMark into each node instance
        assert color in [A,B]
        self.color=color
        self.prev = prev_node
        self.next = None
        if prev_node:
          prev_node.next = self
    def __str__(self):
      return str(self.leftMark)+' '+self.color
'''some test data      
_1 = Node(11) 
_2 = Node(22, _1, B)
_3 = Node(33, _2)
_4 = Node(44, _3, B)
_5 = Node(55, _4)
_6 = Node(66, _5, B)
_7 = Node(77, _6)
_8 = Node(88, _7, B)
_9 = Node(99, _8)'''
class DoublyLinkedList(object):
  def __init__(self, head):
    assert head is not None
    self.head=head
    
  @staticmethod  
  def link2(node1, node2):
    assert node1 is not None
    assert node2 is not None
    node1.next = node2
    node2.prev = node1
  #print 3+1 attributes of a node  
  # to support None, this can't be a Node method
  @staticmethod  
  def print3(node): 
    if node:
      nx = node.next
      rightMark = nx.leftMark-1 if nx else sys.maxint
      print node.prev, '<= [', str(node), rightMark, '] =>', node.next
    else:
      print '_none_'
  def dumpList(self, isStrict=False):
    last=0
    dumpCnt=0
    node = self.head
    line=str()
    while 1:
      if node is None:
        line += 'end'
        break
      DoublyLinkedList.print3(node)
      line += str(node) + ' > '
      assert node.leftMark > last; last=node.leftMark
      nx = node.next
      if nx: assert nx.prev == node
      node = nx
      dumpCnt+=1
      assert dumpCnt < 999
    print line, '\n'
    if isStrict:
      assert Node.cnt == dumpCnt

### Above is a fairly reusable doubly-linked list

def solD(intervals, incoming): # dlist-based solution
  Node.cnt=-1 # for isStrict
  gap = head = Node(sys.maxint)
  segmentPointers=list()
  leftMarks=list()
  for a,b in intervals: # b is left mark of ensuing gap
    #print a, b
    itv = Node(a, gap)
    gap = Node(b, itv, B)
    segmentPointers.extend([itv,gap])
    leftMarks.extend([a,b]) # b is left mark of a gap segment
  head = head.next
  head.prev=None
  dlist = DoublyLinkedList(head)
  dlist.dumpList(True)  
  # dlist constructed :)
  incomingEnd = incoming[1]
  incoming[1] -= 1 # to get its rightMark
  segP,segQ=[segmentPointers[bisect.bisect_right(leftMarks, i)-1] for i in incoming]
  DoublyLinkedList.print3(segP)
  DoublyLinkedList.print3(segQ)
  
  # now the various cases
  if segP.color == A == segQ.color:
    print 'bridge case'
    gap = segQ.next
    DoublyLinkedList.link2(segP, gap)
    return dlist
  elif segP.color == B == segQ.color:
    nextInterval = segQ.next
    newInterval = Node(incoming[0], segP)
    if segP is segQ:
      print 'tiny-interval-in-gap case like [23,24]'
      newGap = Node(incomingEnd, newInterval, B)
      DoublyLinkedList.link2(newGap, nextInterval)
      return dlist
    print 'wipeout case like [23,87]'
    DoublyLinkedList.link2(newInterval, segQ)
    segQ.leftMark = incomingEnd
    return dlist
  
def main():
  ret=solD([[11,22],[33,55],[66,77],[88,100],[122,166]], [33,76])
  if ret: ret.dumpList()
  
  # 4 -> hits the [3-4]
  # 8 -> hits the [7-7]
  #DoublyLinkedList(_1).dumpList() # unit test
main()
'''Req: https://bintanvictor.wordpress.com/2018/07/29/merge-intervals/
'''