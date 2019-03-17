'''todo: use the horizontal print
'''
class Node:
  def __init__(self, val):
    self.l_child = None
    self.r_child = None
    self.data = val
def add(root, node):
  if root is None: root = node
  else:
    if root.data > node.data:
      if root.l_child is None: root.l_child = node
      else: add(root.l_child, node)
    else:
      if root.r_child is None: root.r_child = node
      else: add(root.r_child, node)
def in_order_print(node, depth=0): 
  if node is None: return
  in_order_print(node.l_child, depth+1)
  print ' ' *3*depth + str(node.data)
  in_order_print(node.r_child, depth+1)

def pre_order_print(root):
  if not root: return    
  print root.data
  pre_order_print(root.l_child)
  pre_order_print(root.r_child)  
def main():
  rt = Node(3)
  add(rt, Node(7))
  add(rt, Node(1))
  add(rt, Node(5))
  in_order_print(rt)
main()