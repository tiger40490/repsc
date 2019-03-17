'''todo: use the horizontal print
'''
class Node:
  def __init__(self, val):
    self.l_child = None
    self.r_child = None
    self.data = val
def binary_insert(root, node):
  if root is None: root = node
  else:
    if root.data > node.data:
      if root.l_child is None: root.l_child = node
      else: binary_insert(root.l_child, node)
    else:
      if root.r_child is None: root.r_child = node
      else: binary_insert(root.r_child, node)
def in_order_print(root, depth=0): 
  if root is None: return
  in_order_print(root.l_child, depth+1)
  print ' '*3*depth + str(root.data)
  in_order_print(root.r_child, depth+1)

def pre_order_print(root):
  if not root:
    return    
  print root.data
  pre_order_print(root.l_child)
  pre_order_print(root.r_child)  
def main():
  r = Node(3)
  binary_insert(r, Node(7))
  binary_insert(r, Node(1))
  binary_insert(r, Node(5))
  print "in order:"
  in_order_print(r)
  print "pre order"
  pre_order_print(r)
main()