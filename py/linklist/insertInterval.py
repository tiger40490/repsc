'''
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
        self.next = None
        if prev_node:
          prev_node.next = self
    def __str__(self):
      return str(self.leftMark)+' '+self.color
      
    ''' print 3 attributes of a node  
    '''
    def print3(self):
      nx = self.next
      rightMark = nx.leftMark-1 if nx else sys.maxint
      print '[', self, rightMark, '] =>', self.next

class DoublyLinkedList(object):
  def __init__(self, head):
    assert head is not None
    self.head=head
    
  @staticmethod  
  def link2(node1, node2):
    assert node1 is not None
    assert node2 is not None
    node1.next = node2
    
  def dumpList(self, isStrict=False):
    last=0
    dumpCnt=0
    node = self.head
    line=str()
    while 1:
      if node is None:
        line += 'end'
        break
      node.print3()
      line += str(node) + ' '
      assert node.leftMark > last; last=node.leftMark
      nx = node.next
      node = nx
      dumpCnt+=1
      assert dumpCnt < 999
    print 'returning', line, '\n'
    if isStrict:
      assert Segment.cnt == dumpCnt
    return line

### Above is a fairly reusable doubly-linked list
def solD(intervals, incoming): # dlist-based solution
  assert len(intervals)>1 
  assert incoming[0] < incoming[1]  
  if incoming[1] < intervals[0][0]:
    print 'incoming interval rightMark is very low. This is LOW case, like [1,2]'
    intervals.insert(0, incoming)
    
  elif incoming[0] < intervals[0][0]:
    print 'incoming interval leftMark is very low, like [2,13]' 
    intervals[0][0] = incoming[0]
    
  Segment.cnt=-1 # for isStrict
  gap = head = Segment(sys.maxint)
  segments=list()
  for a,b in intervals: # b is left mark of ensuing gap
    itv = Segment(a, gap)
    gap = Segment(b, itv, B)
    segments.extend([itv,gap])
  head = head.next
  dlist = DoublyLinkedList(head)
  # # dlist constructed :)
  recur(incoming, segments)
  return dlist.dumpList() 
  
def recur(incoming, segments):  
  print 'incoming =', incoming
  incomingEnd = incoming[1]
  incoming[1] -= 1 # to get its rightMark
  
  leftMarks=[node.leftMark for node in segments]
  idx = [bisect.bisect_right(leftMarks, i)-1 for i in incoming]
  segP,segQ=[segments[j] for j in idx]
  
  if segP.color == B and incoming[0] == segP.leftMark:
    print 'adjusting incoming left mark'
    return recur([incoming[0]-1, incomingEnd], segments)
  if segQ.color == B and segQ.next and incomingEnd == segQ.next.leftMark:
    print 'adjusting incoming right mark'
    return recur([incoming[0], incomingEnd+1], segments)
    
  segP.print3()
  segQ.print3()
  assert segP.leftMark <= segQ.leftMark
  
  # now the various cases
  if segP.color == A == segQ.color:
    print 'bridge case, like [33,76], or even [33,34]'
    DoublyLinkedList.link2(segP, segQ.next)
  elif segP.color == B == segQ.color:
    if segP is segQ:
      print 'tiny-interval-in-gap case like [23,24]'
      nextInterval = segQ.next
      newInterval = Segment(incoming[0], segP)
      newGap = Segment(incomingEnd, newInterval, B)
      if nextInterval is not None:
        DoublyLinkedList.link2(newGap, nextInterval)
    else:
      print 'swallow-up case like [23,87]'
      segP.next.leftMark=incoming[0] 
      return recur([incoming[0], incomingEnd], segments)
  elif segP.color == A and B == segQ.color:
    print 'bridge-Into-gap case, like [33,111] or even [33,61]'
    DoublyLinkedList.link2(segP, segQ)
    segQ.leftMark = incomingEnd
  elif segP.color == B and A == segQ.color:
    print 'bridge-From-gap case, like [30,90] or even [30,40]'
    DoublyLinkedList.link2(segP, segQ)
    segQ.leftMark=incoming[0]
  else:
     assert 1==0  
    
def main():
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [165,169]) =='11 A 22 B 33 A 55 B 66 A 77 B 88 A 99 B 122 A 169 B end')
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [168,169]) =='11 A 22 B 33 A 55 B 66 A 77 B 88 A 99 B 122 A 166 B 168 A 169 B end')
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [2,11]) =='2 A 22 B 33 A 55 B 66 A 77 B 88 A 99 B 122 A 166 B end')
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [2,4]) =='2 A 4 B 11 A 22 B 33 A 55 B 66 A 77 B 88 A 99 B 122 A 166 B end')
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [33,34]) =='11 A 22 B 33 A 55 B 66 A 77 B 88 A 99 B 122 A 166 B end')
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [33,76]) =='11 A 22 B 33 A 77 B 88 A 99 B 122 A 166 B end')
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [23,24]) =='11 A 22 B 23 A 24 B 33 A 55 B 66 A 77 B 88 A 99 B 122 A 166 B end')
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [23,87]) =='11 A 22 B 23 A 87 B 88 A 99 B 122 A 166 B end')  
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [33,61]) =='11 A 22 B 33 A 61 B 66 A 77 B 88 A 99 B 122 A 166 B end')
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [33,111]) =='11 A 22 B 33 A 111 B 122 A 166 B end')
  assert(solD([[11,22],[33,55],[66,77],[88,99],[122,166]], [30,40]) =='11 A 22 B 30 A 55 B 66 A 77 B 88 A 99 B 122 A 166 B end')
  
  #DoublyLinkedList(_1).dumpList() # unit test
main()
'''Req: https://bintanvictor.wordpress.com/2018/07/29/merge-intervals/
'''