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
      
    ''' print 3+1 attributes of a node  
    '''
    def print3(self):
      nx = self.next
      rightMark = nx.leftMark-1 if nx else sys.maxint
      print self.prev, '<= [', self, rightMark, '] =>', self.next
    
#some test data      
_1 = Segment(11) 
_2 = Segment(22, _1, B)
_3 = Segment(33, _2)
_4 = Segment(44, _3, B)
_5 = Segment(55, _4)
_6 = Segment(66, _5, B)
_7 = Segment(77, _6)
_8 = Segment(88, _7, B)
_9 = Segment(99, _8)
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
      if nx: assert nx.prev == node
      node = nx
      dumpCnt+=1
      assert dumpCnt < 999
    print 'returning', line, '\n'
    if isStrict:
      assert Segment.cnt == dumpCnt
    return line

### Above is a fairly reusable doubly-linked list
def main():
  DoublyLinkedList(_1).dumpList() # unit test
main()