'''todo: 
showcase: 
'''
from collections import deque
from pprint import pprint
from datetime import datetime
bigMatSize=1000
if bigMatSize > 7: 
    sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)
m = list() 
pair=list()
revisits = dict()

def test9():
  global m
  m = [[1 for x in xrange(bigMatSize)] for y in xrange(bigMatSize)]
  assert len(m) == bigMatSize and len(m[0]) == bigMatSize
  return 15305440000
def test9b():
  global m
  m = [[1 for x in xrange(bigMatSize)] for y in xrange(bigMatSize)]
  assert len(m) == bigMatSize and len(m[0]) == bigMatSize
  m[-1][-1]=0
  return 0
def test4():
  global m
  m.append([1,1,1])
  m.append([1,0,1])
  m.append([1,1,1])
  return 2
def test3():
  global m
  m.append([1,1,0,1])
  m.append([0,0,1,1])
  m.append([1,1,1,1])
  return 0
def test2():
  global m
  m.append([1,1,1,1])
  m.append([1,1,1,1])
  m.append([1,1,1,1])
  return 10 # Q9 test case
def test1():
  m.append([1,1,0,1])
  m.append([1,1,1,1])
  del pair[:]
  pair.extend([0,1], [-1:-2])
  return true
class Q: #class based on collections.deque
    def __init__(self):
        self.list = deque()
    def enQ(self, item):
        self.list.append(item)
    def deQ(self): 
        return self.list.popleft() # throws error if empty

score=list() #shadow matrix

def readScore(r,c, verbose=1):
  '''Created for revisit accounting, which hurts performance. 
  Comment out next line after verifying revisits.  
  '''
  if verbose: 
    addr=(r,c); revisits[addr] = revisits.get(addr, 0) + 1  
    assert r>=0 and c>=0
  return score[r][c]
def startBFT(verbose): 
  global finalCnt, score
  # 0 means unknown
  score=[[0 for _ in xrange(width)] for _ in xrange(height)]
  score[0][0] = 1
  q = Q()
  q.enQ((1,0))
  q.enQ((0,1))
  while q.list:
    r,c = q.deQ()
    if readScore(r,c,verbose) > 0: continue # See Keynote in blog
    if m[r][c] == 0: continue
    tmp  = readScore(r-1, c,verbose) if r>0 else 0
    tmp += readScore(r, c-1,verbose) if c>0 else 0
    assert tmp > 0
    score[r][c] = tmp 
    if verbose: print r,c,' --> score set to ', score[r][c]   
    if r < height-1 : 
        q.enQ((r+1, c))
    if c < width-1 :
        q.enQ((r, c+1))
  finalCnt = score[-1][-1]

def main():
  work(test1)
  return
  work(test2)
  work(test3)
  work(test4)
  
  startTime=datetime.now()
  work(test9)
  print (datetime.now()-startTime).total_seconds(), 'seconds'
  work(test9b)
main()
''' Req: https://bintanvictor.wordpress.com/2018/08/11/check-2-matrix-nodes-are-connected/
'''
