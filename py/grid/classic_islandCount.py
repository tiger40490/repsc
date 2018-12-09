'''
reusable technique -- outer loop to visit every matrix node, but most of them were already visited in earlier graph walk, so use "grey" to avoid revisiting

showcase collections.deque
showcase myFunc( * xy) which calls myFunc(xy[0], xy[1])
'''
width, height = 0,0
m = list() 
seen = 0
islands = 0
isVerbose = True
b=1 # black
w=0 # white
g=2 # grey
# ^^^^^^^^^ globals ^^
def readCell(r,c): # utility to return None if out of bounds
  global seen
  if 0<=r and r<height   and   0<=c and c<width:
    origColor = m[r][c]
    if origColor != g: 
      seen += 1
      m[r][c] = g # grey to indicate seen
      if isVerbose: print r,c,'painted grey and incremented seen to', seen	  
    return origColor
  return None # out of bounds
  
def dft(r,c): # SOF for 1000x1000 matrix :(
  if readCell(r, c+1) == b: coverEntireIsland(r,c+1)
  if readCell(r, c-1) == b: coverEntireIsland(r,c-1)
  if readCell(r+1, c) == b: coverEntireIsland(r+1,c)
  tmp = readCell(r-1, c); assert tmp is None or tmp == g, 'i doubt we ever need to explore upward'
  
def checkEnqueue(pair, queue):
  if readCell( * pair) == b: queue.append(pair)
def bft(aa,bb): # avoids deep recursion stack :)
  from collections import deque; queue = deque()
  queue.append((aa,bb))
  while(queue):
    r,c = queue.popleft()
    checkEnqueue((r,c+1), queue)
    checkEnqueue((r,c-1), queue)
    checkEnqueue((r+1,c), queue)
    checkEnqueue((r-1,c), queue)
def coverEntireIsland(r,c): # bft/dft both OK. BFT turns out a bit tricky to implement
  bft(r,c)      
def solve1(m):
  global seen, islands; islands = seen = 0
  global width,height; height = len(m); width = len(m[0]) # to ease readCell()
  global isVerbose; isVerbose = width*height < 99
  if isVerbose: dump(m)
  for r in xrange(height):
    for c in xrange(width):
      color = readCell(r,c)
      if color == b: 
        islands += 1
        coverEntireIsland(r,c)
  assert seen == width*height
  print islands, '<-- islands found. Game over'
  return islands
def test9():
  del m[:]
  bigMatSize=1000
  m.extend( [[b for _ in xrange(bigMatSize)] for _ in xrange(bigMatSize)] )
  assert len(m) == bigMatSize and len(m[0]) == bigMatSize
  assert 1 == solve1(m)  
def test1():
  del m[:]
  m.append([w, b, w, w, w])
  m.append([w, b, w, w, b])
  m.append([b, w, w, b, b])
  m.append([w, w, w, w, w])
  m.append([b, b, b, w, b])
  assert 5 == solve1(m)  
def dump(m):
  for r in xrange(len(m)):
    for c in xrange(len(m[0])):
      print m[r][c],
    print
def main():
  test1()
  test9()
main()
'''https://bintanvictor.wordpress.com/2018/02/23/binary-matrix-cluster-count-deepak/
'''
