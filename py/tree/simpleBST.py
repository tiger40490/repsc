'''
showcase random.shuffle a list
todo: delete is too much work. Need to find the max node in the left subtree to replace the deleted node
'''
class Node:
  def __init__(self, val):
    self.le = None
    self.ri = None
    self.data = val
def add(cur, val):
  new = Node(val)
  if cur is None: cur = new
  else:
    if cur.data == new.data: print new.data,'is dupe'; return
    elif cur.data > new.data:
      if cur.le is None: cur.le = new
      else: add(cur.le, val)
    else:
      if cur.ri is None: cur.ri = new
      else: add(cur.ri, val)
def in_order_print(node, depth=0): 
  if node is None: 
    print ' ' *3*depth + ']'
    return
  in_order_print(node.le, depth+1)
  print ' ' *3*depth + str(node.data)
  in_order_print(node.ri, depth+1)

def pre_order_print(node, depth=0):
  if node is None: 
    print ' ' *3*depth + ']'
    return
  print ' ' *3*depth + str(node.data)
  pre_order_print(node.le, depth+1)
  pre_order_print(node.ri, depth+1)  
def main():
  cnt=20
  rt = Node(cnt/2)
  x = range(cnt)
  import random; random.shuffle(x)
  for i in x: add(rt, i)
  
  in_order_print(rt)
  pre_order_print(rt)
main()