m = list() 
revisits = dict()
def test2():
  global m
  m.append([1,1,1,1])
  m.append([1,1,1,1])
  m.append([1,1,1,1])
def test1():
  global m
  m.append([1,1,0,1])
  m.append([1,1,1,1])
def start(r,c): 
  global finalCnt, revisits
  addr=(r,c)
  revisits[addr] = revisits.get(addr, 0) + 1
  if revisits[addr] > 4: print addr, 'visited', revisits[addr], 'times :('
  if m[r][c]==0: #dead end
    return
  if r < height-1:
    start(r+1, c)
  if c < width-1:
    start(r, c+1)
    
  if r == height-1 and c == width-1:
    finalCnt += 1
    print 'incremented finalCnt to', finalCnt
def work(setup1test):
  global m, width, height, finalCnt, revisits
  m = list()
  setup1test()
  height, width = len(m), len(m[0])
  finalCnt=0
  revisits=dict()
  print '-----------'
  
  start(0,0)
def main():
  work(test1)
  work(test2)
main()
# Req: https://bintanvictor.wordpress.com/2018/05/28/count-paths-between-2-tree-nodes/
