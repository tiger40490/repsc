'''todo: use the horizontal print
'''
class Node:
  def __init__(self, val):
    self.le = None
    self.ri = None
    self.data = val
def add(root, node):
  if root is None: root = node
  else:
    if root.data > node.data:
      if root.le is None: root.le = node
      else: add(root.le, node)
    else:
      if root.ri is None: root.ri = node
      else: add(root.ri, node)
def in_order_print(node, depth=0): 
  if node is None: return
  in_order_print(node.le, depth+1)
  print ' ' *3*depth + str(node.data)
  in_order_print(node.ri, depth+1)

def pre_order_print(node):
  if not node: return    
  print node.data
  pre_order_print(node.le)
  pre_order_print(node.ri)  
def main():
  rt = Node(3)
  add(rt, Node(7))
  add(rt, Node(1))
  add(rt, Node(5))
  in_order_print(rt)
  pre_order_print(rt)
main()