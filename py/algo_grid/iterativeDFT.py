''' showcase sum of matrix
'''
m=list()
def mat():
    del m[:]
    m.append([1,1,0,1])
    m.append([0,1,1,1])
    m.append([1,0,1,1])
    #return m
def visit(node, seen):
  if node in seen: return
  r,c = node
  R = len(m) -1 
  C = len(m[0]) -1
  seen.append(node); print node, ':', m[r][c]
  if r>0 and m[r-1][c] == 1: # go north
    visit((r-1,c), seen)
  if r<R and m[r+1][c] == 1: # go south
    visit((r+1,c), seen)
  if c<C and m[r][c+1] == 1: # go east
    visit((r,c+1), seen)
  if c>0 and m[r][c-1] == 1: # go west
    visit((r,c-1), seen)
  
def startRecursive(dummy, expected):
  # let's start from north west corner and visit all connected nodes
  seen = list() # all nodes already printed
  visit((0,0), seen)
  assert len(seen) == expected <= sum(sum(m, []))
  return len(seen)
  
startRecursive(mat(),8)
''' A simple demo of an iterative DFT. At the end of the scan, return the number of reachable and visible (non-zero) nodes

'''