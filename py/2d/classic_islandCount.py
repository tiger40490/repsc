width, height = 0,0
m = list() 
seen = 0
islands = 0
# ^^ globals ^^
def readCell(r,c): # utility to return None if out of bounds
  global seen
  if 0<=r and r<height and 0<=c and c<width:
    origColor = m[r][c]
    if origColor != 'g': 
      seen += 1
      m[r][c] = 'g' # grey to indicate seen
      print r,c,'painted grey and incremented seen to', seen	  
    return origColor
  return None # out of bounds
  
def dft(r,c): # find all black cells connected and repaint them grey
  if readCell(r, c+1) == 'b': coverEntireCluster(r,c+1)
  if readCell(r, c-1) == 'b': coverEntireCluster(r,c-1)
  if readCell(r+1, c) == 'b': coverEntireCluster(r+1,c)
  tmp = readCell(r-1, c); assert tmp is None or tmp == 'g'# i doubt we ever need to explore upward
  
def bft(aa,bb): 
  queue=list()
  queue.insert(0, (aa,bb))
  while(queue):
    r,c = queue.pop()
    if readCell(r, c+1) == 'b': queue.insert(0, (r,c+1))
    if readCell(r, c-1) == 'b': queue.insert(0, (r,c-1))
    if readCell(r+1, c) == 'b': queue.insert(0, (r+1,c))
    if readCell(r-1, c) == 'b': queue.insert(0, (r-1,c))
def work():
  global islands
  for r in range(0,height,1):
    for c in range(0,width,1):
      #if seen >= width*height: return myReturn()
      color = readCell(r,c)
      if color == 'b': 
        islands += 1
        coverEntireCluster(r,c)
  assert seen == width*height
  return myReturn()
def coverEntireCluster(r,c): # bft/dft both OK. BFT turns out a bit tricky to implement
  dft(r,c)      
def populate():
  global m, width, height
  m.append(['w', 'b', 'w', 'w', 'w'])
  m.append(['w', 'b', 'w', 'w', 'b'])
  m.append(['b', 'w', 'w', 'b', 'b'])
  m.append(['w', 'w', 'w', 'w', 'w'])
  m.append(['b', 'b', 'b', 'w', 'b'])
  height = len(m)
  width = len(m[0])
def myReturn():
  print islands, '<-- clusters found. Game over'
def dump():
  for r in xrange(len(m)):
    for c in xrange(width):
      print m[r][c],
    print
def main():
  populate()
  dump()
  work()
  #dump()
main()
'''https://bintanvictor.wordpress.com/2018/02/23/binary-matrix-cluster-count-deepak/
'''
