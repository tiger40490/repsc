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
  print leftMarks 
  seg=[segmentPointers[bisect.bisect_left(leftMarks, i)-1] for i in incoming]
  DoublyLinkedList.print3(seg[0])
  DoublyLinkedList.print3(seg[1])
  
  # now the different cases
  #if segment1.color == A:
    
def main():
  solD([[1,2],[3,5],[6,7],[8,10],[12,16]], [4,8])
  # 4 -> hits the [3-4]
  # 8 -> hits the [7-7]
  #DoublyLinkedList(_1).dumpList() # unit test
main()
'''Req: https://bintanvictor.wordpress.com/2018/07/29/merge-intervals/
'''