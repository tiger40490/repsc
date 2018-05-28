m = list() 
revisits = dict()
def test3():
  global m
  tmp=100
  m = [[1 for x in xrange(tmp)] for y in xrange(tmp)]
  assert len(m) == tmp and len(m[0]) == tmp
def test2():
  global m
  m.append([1,1,1,1])
  m.append([1,1,1,1])
  m.append([1,1,1,1])
def test1():
  global m
  m.append([1,1,0,1])
  m.append([1,1,1,1])
def start(r,c, verbose): 
  global finalCnt, revisits
  addr=(r,c)
  revisits[addr] = revisits.get(addr, 0) + 1
  if verbose and revisits[addr] > 4: print addr, 'visited', revisits[addr], 'times :('
  if m[r][c]==0: #dead end
    return
  if r < height-1:
    start(r+1, c, verbose)
  if c < width-1:
    start(r, c+1, verbose)
    
  if r == height-1 and c == width-1:
    finalCnt += 1
    if verbose: print 'incremented finalCnt to', finalCnt
def work(setup1test, verbose=1):
  global m, width, height, finalCnt, revisits
  m = list()
  setup1test()
  height, width = len(m), len(m[0])
  finalCnt=0
  revisits=dict()
  print '-----------'
  
  start(0,0, verbose)
def main():
  #work(test3, verbose=0)
  #return
  work(test2)
  work(test1)
main()
# Req: https://bintanvictor.wordpress.com/2018/05/28/count-paths-between-2-tree-nodes/
