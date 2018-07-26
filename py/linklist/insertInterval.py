'''
showcase double linked list
'''
import sys, bisect
A='A'; B='B'
class Node(object): # each node is a segment
    cnt=0
    def __init__(self, leftMark, prev_node=None, color=A):
        assert leftMark > 0
        Node.cnt+=1
        self.leftMark = leftMark # rightMark would be self.next.leftMark-1. I choose not to save rightMark into each node instance
        assert color in 'AB'
        self.color=color
        self.prev = prev_node
        self.next = None
        if prev_node:
          prev_node.next = self
    def __str__(self):
      return str(self.leftMark)+' '+self.color
_1 = Node(11) 
_2 = Node(22, _1, B)
_3 = Node(33, _2)
_4 = Node(44, _3, B)
_5 = Node(55, _4)
_6 = Node(66, _5, B)
_7 = Node(77, _6)
_8 = Node(88, _7, B)
_9 = Node(99, _8)
head=_1

def print3(node): #print 3+1 attributes of a node
  if node:
    nx = node.next
    rightMark = nx.leftMark-1 if nx else sys.maxint
    print node.prev, '<= [', str(node), rightMark, '] =>', node.next
  else:
    print '_none_'
def dumpList(isStrict=False):
  last=0
  dumpCnt=0
  node = head
  line=str()
  while 1:
    if node is None:
      line += 'end'
      break
    print3(node)
    line += str(node) + ' > '
    assert node.leftMark > last; last=node.leftMark
    nx = node.next
    if nx: assert nx.prev == node
    node = nx
    dumpCnt+=1
    assert dumpCnt < 999
  print line
  if isStrict:
    assert Node.cnt == dumpCnt

### Above is a fairly reusable doubly-linked list
def solD(intervals, incoming): # dlist-based solution
  global head
  Node.cnt=-1
  gap = head = Node(sys.maxint)
  nodePointers=list()
  for a,b in intervals: # b is left mark of ensuing gap
    #print a, b
    itv = Node(a, gap)
    gap = Node(b, itv, B)
    nodePointers.extend([itv,gap])
  head = head.next
  head.prev=None
  dumpList(True)  
  # dlist constructed :)
  li = [node.leftMark for node in nodePointers]
  print li
  idx = [bisect.bisect_right(li, i)-1 for i in incoming]
  print idx
  print3(nodePointers[idx[0]])
  print3(nodePointers[idx[1]])
  
def main():
  solD([[1,2],[3,5],[6,7],[8,10],[12,16]], [4,8])
  #dumpList()
main()
'''Req: https://bintanvictor.wordpress.com/2018/07/29/merge-intervals/

first let's create a dumpList() function

'''