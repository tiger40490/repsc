class Node(object):
    def __init__(self, data, left_node=None, right_node=None):
        self.data = data
        self.le = left_node
        self.ri = right_node
'''   5
  2       7
 1 3    6   8
             9
'''
_9=Node(9)
_8=Node(8, None, _9)
_6=Node(6, None, None)
_7=Node(7, _6, _8)
_3=Node(3)
_1=Node(1)
_2=Node(2, _1, _3)
_5=Node(5, _2, _7) 
root = _5
def visit(node):
    if node.le: visit(node.le)
    print node.data
    if node.ri: visit(node.ri)        
def inOrderDftRecursive():
    print '------- recursive ------'
    visit(root)
##############  
def dump(st):
  for node, state in st:  print ' ', node.data,
  print 

''' the 2nd element in each stack element is 
i for initial
L for after printing left-child
'''
def inOrderDftIterative():
  print '------- iterative ------'
  stack = [[root,'i'] ]
  while(stack):
    frame = stack[-1]
    node, state = frame
    print 'stack top is', node.data, state
    if state == 'R':
      stack.pop()
      continue
    if node.le is not None and state == 'i': 
      stack.append([node.le,'i'])
      print "after append le",; dump(stack)
      frame[1] = 'L'    
      continue    
    print '------> ', node.data
    
    if node.ri is not None: 
      stack.append([node.ri,'i'])
      print "after append ri",; dump(stack)
      frame[1] = 'R'    
      continue
    stack.pop(); print "after pop",; dump(stack)

def main():
    inOrderDftIterative()
    inOrderDftRecursive()

main()