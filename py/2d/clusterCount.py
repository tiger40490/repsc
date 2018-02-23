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
def dst(r,c): # find all black cells connected and repaint them grey
  if readCell(r, c+1) == 'b': treewalk(r,c+1)
  if readCell(r, c-1) == 'b': treewalk(r,c-1)
  if readCell(r+1, c) == 'b': treewalk(r+1,c)
  if readCell(r-1, c) == 'b': treewalk(r-1,c)
  
def work():
  global islands
  for r in range(0,height,1):
    for c in range(0,width,1):
      if seen >= width*height: return myReturn()
      color = readCell(r,c)
      if color == 'b': 
        islands += 1
        treewalk(r,c)
  assert seen == width*height
  return myReturn()
def treewalk(r,c):
  dst(r,c)      
def populate():
  global m, width, height
  m.append(['b', 'b', 'w', 'b', 'b'])
  m.append(['b', 'b', 'w', 'w', 'b'])
  m.append(['b', 'w', 'w', 'w', 'w'])
  m.append(['w', 'b', 'w', 'w', 'w'])
  m.append(['b', 'w', 'w', 'w', 'w'])
  height = len(m)
  width = len(m[0])
  
def myReturn():
  print islands, '<-- clusters found. Game over'
  return None #return value not needed

def dump():
  for r in xrange(len(m)):
    for c in xrange(width):
      print m[r][c],
    print
def main():
  populate()
  work()
  #dump()
main()
'''
Input : mat[][] = {{1, 1, 0, 0, 0},
                   {0, 1, 0, 0, 1},
                   {0, 0, 0, 1, 1},
                   {0, 0, 0, 0, 0},
                   {1, 0, 1, 0, 1} 
Output : 5 
'''