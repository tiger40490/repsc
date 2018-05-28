# todo: use more efficient queue
import sys, os
bigMatSize=10
if bigMatSize > 9: 
    sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)
m = list() 
revisits = dict()

def test3():
  global m
  m = [[1 for x in xrange(bigMatSize)] for y in xrange(bigMatSize)]
  assert len(m) == bigMatSize and len(m[0]) == bigMatSize
def test2():
  global m
  m.append([1,1,1,1])
  m.append([1,1,1,1])
  m.append([1,1,1,1])
def test1():
  global m
  m.append([1,1,0,1])
  m.append([1,1,1,1])
def startDFT(r,c, verbose): 
  global finalCnt, revisits
  addr=(r,c)
  revisits[addr] = revisits.get(addr, 0) + 1
  if verbose and revisits[addr] > 4: print addr, 'visited', revisits[addr], 'times :('
  if m[r][c]==0: #dead end
    return
  if r < height-1: #move down before moving right
    startDFT(r+1, c, verbose)
  if c < width-1:
    startDFT(r, c+1, verbose)
    
  if r == height-1 and c == width-1:
    finalCnt += 1
    if verbose: print 'incremented finalCnt to', finalCnt
######## non-recursive BFT solution
class Q: #simple class
    def __init__(self):
        self.list = [] # faster than list()
    def enq(self, item):
        self.list.insert(0,item)
        #print 'pushed', item.data
    def deq(self): return self.list.pop() # throws error if empty
   
def startBFT(verbose=1): 
  global finalCnt
  score=[[0 for x in xrange(width)] for y in xrange(height)]
  score[0][0] = 1
  q = Q()
  q.enq((1,0))
  q.enq((0,1))
  while q.list:
    r,c = q.deq()
    #print r,c
    if score[r][c]==0:
      score[r][c] += score[r-1][c] if r>0 else 0
      score[r][c] += score[r][c-1] if c>0 else 0
      if verbose: print r,c,' --> score set to ', score[r][c]    
    if r < height-1 and score[r+1][c]==0 and m[r+1][c]: 
      q.enq((r+1, c))
    if c < width-1  and score[r][c+1]==0 and m[r][c+1]: 
      q.enq((r, c+1))
  finalCnt = score[height-1][width-1]
def work(setup1test, verbose=1):
  global m, width, height, finalCnt, revisits
  m = list()
  setup1test()
  height, width = len(m), len(m[0])
  finalCnt=0
  revisits=dict()
  
  startBFT(verbose)  
  #startDFT(0,0, verbose) # tested but inefficient
  print '-----------> finalCnt =', finalCnt
def main():
  work(test1)
  work(test2)
  work(test3, verbose=0)
main()
''' Req: https://bintanvictor.wordpress.com/2018/05/28/count-paths-between-2-tree-nodes/
'''
