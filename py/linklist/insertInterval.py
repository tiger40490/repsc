A='A'
B='B'
class Node(object): # each node is a segment
    cnt=0
    def __init__(self, leftMark, prev_node=None, color=A):
        assert leftMark > 0
        Node.cnt+=1
        self.leftMark = leftMark # rightMarkDerived would be next.leftMark-1
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

def print3(node):
  if node:
    a = node.next
    rightMarkDerived = a.leftMark-1 if a else 99999
    print node.prev, '<= [', str(node), rightMarkDerived, '] =>', node.next
  else:
    print '_none_'
def dump():
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
    next = node.next
    if next: assert next.prev == node
    node = next
    dumpCnt+=1
    assert dumpCnt < 999
  print line
  assert Node.cnt == dumpCnt

def solD(): # dlist-based solution
  pass

def main():
  dump()
main()
'''Req: https://bintanvictor.wordpress.com/2018/07/29/merge-intervals/

first let's create a dump() function

'''