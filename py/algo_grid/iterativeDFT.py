''' 
showcase sum of matrix
showcase passing a function output into a method, where the function mat() only updates a global variable and implicitly returns None. The side effect of mat() is what we need.
'''
m=list()
def mat():
    del m[:]
    m.append([1,2,0,8])
    m.append([0,3,4,7])
    m.append([1,0,5,6])
def startRecursive(_, expected):
  def visit(node, seen):
      if node in seen: return
      r,c = node
      R = len(m) -1 
      C = len(m[0]) -1
      seen.append(node); print node, ':', m[r][c]
      if r>0 and m[r-1][c] > 0: visit((r-1,c), seen) # go north
      if r<R and m[r+1][c] > 0: visit((r+1,c), seen) # go south
      if c<C and m[r][c+1] > 0: visit((r,c+1), seen) # go east
      if c>0 and m[r][c-1] > 0: visit((r,c-1), seen) # go west
  # end of nested function. Let's start from north west corner and visit all connected nodes
  print '    v v v    recursive    v v v'
  seen = list() # all nodes already printed
  visit((0,0), seen)
  assert len(seen) == expected <= sum(sum(m, []))
  return seen
  
def startIterative(_, expected):
  stack = [(0,0)]; seen=list()
  R = len(m) -1 
  C = len(m[0]) -1    
  while len(stack):
    node = stack.pop()
    if node in seen: continue
    r,c = node
    seen.append(node); print node, ':', m[r][c]
    
    if c>0 and m[r][c-1] > 0: stack.append((r,c-1)) # go west
    if c<C and m[r][c+1] > 0: stack.append((r,c+1)) # go east
    if r<R and m[r+1][c] > 0: stack.append((r+1,c)) # go south
    if r>0 and m[r-1][c] > 0: stack.append((r-1,c)) # go north
  assert len(seen) == expected <= sum(sum(m, []))
  recursiveResult = startRecursive(None, expected)
  assert seen == recursiveResult
  return seen
    
startIterative(mat(),8)
''' A simple demo of an iterative DFT. 
Req: At the end of the scan, return the sequence of reachable and   visible(i.e. non-zero) nodes

'''