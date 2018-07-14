class Node(object):
  def __init__(self, data, next_node=None):
    self.data = data
    self.next = next_node
_7 = Node(7)
_6 = Node(6, _7)
_5 = Node(5, _6)
_4 = Node(4, _5)
_3 = Node(3, _4)
_2 = Node(2, _3)
_1 = Node(1, _2)
root = _1
### above is reusable set-up
def dump():
  node = root
  while(1):
    if node is None:
      print 'end'
      break
    print node.data, '->',
    node = node.next
def rev():
  global root #otherwise, compiler gives misleading errors
  pre = root
  me = root  
  while(1):
    ne = me.next
    me.next = pre;print me.data, '<- link fixed internally'
    if ne is None: # exit condition
      root.next = None
      root = me
      break
    pre = me
    me = ne
K=2
def main():
  dump()
  rev()
  dump()
main()
'''Req: https://bintanvictor.wordpress.com/2018/07/14/reverse-link-list-in-k-groups/
I won't bother to pass all leetcode tests. Real interview will focus on the key points, not those corner cases
'''
