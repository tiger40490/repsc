'''
showcase homemade double linked list
'''
import sys, bisect
A='A' # Above-water 
B='B' # Below-Water
class Segment(object): # each node is a segment
    cnt=0
    def __init__(self, leftMark, prev_node=None, color=A):
        assert leftMark > 0
        Segment.cnt+=1
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
_1 = Segment(11) 
_2 = Segment(22, _1, B)
_3 = Segment(33, _2)
_4 = Segment(44, _3, B)
_5 = Segment(55, _4)
_6 = Segment(66, _5, B)
_7 = Segment(77, _6)
_8 = Segment(88, _7, B)
_9 = Segment(99, _8)'''
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
  # to support None, this can't be a Segment method
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
      assert Segment.cnt == dumpCnt

### Above is a fairly reusable doubly-linked list

def solD(intervals, incoming): # dlist-based solution
  Segment.cnt=-1 # for isStrict
  gap = head = Segment(sys.maxint)
  segmentPointers=list()
  leftMarks=list()
  for a,b in intervals: # b is left mark of ensuing gap
    #print a, b
    itv = Segment(a, gap)
    gap = Segment(b, itv, B)
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
    print 'bridge case, like [33,76], or even [33,34]'
    gap = segQ.next
    DoublyLinkedList.link2(segP, gap)
    return dlist
  elif segP.color == B == segQ.color:
    nextInterval = segQ.next
    newInterval = Segment(incoming[0], segP)
    if segP is segQ:
      print 'tiny-interval-in-gap case like [23,24]'
      newGap = Segment(incomingEnd, newInterval, B)
      DoublyLinkedList.link2(newGap, nextInterval)
      return dlist
    print 'wipeout case like [23,87]'
    DoublyLinkedList.link2(newInterval, segQ)
    segQ.leftMark = incomingEnd
    return dlist
  elif segP.color == A and B == segQ.color:
    print 'bridge-Into-gap case, like [33,111] or even [33,61]'
    DoublyLinkedList.link2(segP, segQ)
    segQ.leftMark = incomingEnd
    return dlist
  elif segP.color == B and A == segQ.color:
    print 'bridge-From-gap case, like [30,90] or even [30,40]'
    DoublyLinkedList.link2(segP, segQ)
    segQ.leftMark=incoming[0]
    return dlist
    
def main():
  ret=solD([[11,22],[33,55],[66,77],[88,100],[122,166]], [30,40])
  if ret: ret.dumpList()
  #DoublyLinkedList(_1).dumpList() # unit test
main()
'''Req: https://bintanvictor.wordpress.com/2018/07/29/merge-intervals/
'''