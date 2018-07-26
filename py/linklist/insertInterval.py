'''
showcase double linked list
'''
A='A'; B='B'
class Node(object): # each node is a segment
    cnt=0
    def __init__(self, leftMark, prev_node=None, color=A):
        assert leftMark > 0
        Node.cnt+=1
        self.leftMark = leftMark # rightMark would be self.next.leftMark-1
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
  defaultRightMark=9999 #I choose not to save rightMark into each node instance
  if node:
    nx = node.next
    rightMark = nx.leftMark-1 if nx else defaultRightMark
    print node.prev, '<= [', str(node), rightMark, '] =>', node.next
  else:
    print '_none_'
def dumpList():
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
  assert Node.cnt == dumpCnt

### Above is a fairly reusable doubly-linked list

def solD(): # dlist-based solution
  pass

def main():
  dumpList()
main()
'''Req: https://bintanvictor.wordpress.com/2018/07/29/merge-intervals/

first let's create a dumpList() function

'''