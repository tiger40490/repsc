class Node(object):
    cnt=0
    def __init__(self, data, prev_node=None, next_node=None):
        assert data > 0
        Node.cnt+=1
        self.data = data
        self.prev = prev_node
        self.next = next_node
_1 = Node(1) 
_2 = Node(2)
_3 = Node(3)
_4 = Node(4)
_5 = Node(5)
_6 = Node(6)
_7 = Node(7)
_8 = Node(8)

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
    assert dumpCnt < 999
  if isAll: 
    assert Node.cnt == 1+dumpCnt

def solD(): # dlist-based solution
  pass

def main():
  dump(sol2(), True)
main()
'''Req: https://bintanvictor.wordpress.com/2018/07/29/merge-intervals/

first let's create a dump() function

'''