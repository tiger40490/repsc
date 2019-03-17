'''todo: delete
todo: if equal, then reject
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

def pre_order_print(node):
  if not node: return    
  print node.data
  pre_order_print(node.le)
  pre_order_print(node.ri)  
def main():
  rt = Node(50)
  add(rt, 77)
  add(rt, 33)
  add(rt, 11)
  add(rt, 66)
  add(rt, 55)
  add(rt, 88)
  add(rt, 44)
  add(rt, 22)
  add(rt, 99)
  add(rt, 33)
  
  in_order_print(rt)
  pre_order_print(rt)
main()