'''
reusable technique -- outer loop to visit every matrix node, but most of them were already visited in earlier graph walk, so use "grey" to avoid revisiting
'''
width, height = 0,0
m = list() 
seen = 0
islands = 0
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
      print r,c,'painted grey and incremented seen to', seen	  
    return origColor
  return None # out of bounds
  
def dft(r,c): # find all black cells connected and repaint them grey
  if readCell(r, c+1) == b: coverEntireIsland(r,c+1)
  if readCell(r, c-1) == b: coverEntireIsland(r,c-1)
  if readCell(r+1, c) == b: coverEntireIsland(r+1,c)
  tmp = readCell(r-1, c); assert tmp is None or tmp == g, 'i doubt we ever need to explore upward'
  
def bft(aa,bb): 
  queue=list()
  queue.insert(0, (aa,bb))
  while(queue):
    r,c = queue.pop()
    if readCell(r, c+1) == b: queue.insert(0, (r,c+1))
    if readCell(r, c-1) == b: queue.insert(0, (r,c-1))
    if readCell(r+1, c) == b: queue.insert(0, (r+1,c))
    if readCell(r-1, c) == b: queue.insert(0, (r-1,c))
def coverEntireIsland(r,c): # bft/dft both OK. BFT turns out a bit tricky to implement
  dft(r,c)      
def solve1(m):
  global width, height, islands
  height = len(m); width = len(m[0]) # to ease readCell()
  dump(m)
  for r in xrange(height):
    for c in xrange(width):
      color = readCell(r,c)
      if color == b: 
        islands += 1
        coverEntireIsland(r,c)
  assert seen == width*height
  print islands, '<-- islands found. Game over'
  return islands
def populate():
  m.append([w, b, w, w, w])
  m.append([w, b, w, w, b])
  m.append([b, w, w, b, b])
  m.append([w, w, w, w, w])
  m.append([b, b, b, w, b])
def dump(m):
  for r in xrange(len(m)):
    for c in xrange(len(m[0])):
      print m[r][c],
    print
def main():
  populate()
  assert 5 == solve1(m)
main()
'''https://bintanvictor.wordpress.com/2018/02/23/binary-matrix-cluster-count-deepak/
'''
