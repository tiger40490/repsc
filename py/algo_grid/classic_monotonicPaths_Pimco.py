'''todo: early exit if either origin or destination is an island, but detecting it could be slower than the main scan.
todo: improve BFT Test 9 performance from 11 sec

* Key idea: DP
* Key idea: BFT doesn't scan the matrix in type-writer zigzag. DFT (not BFT) solution requires recursion within a loop
* Key idea: BFT to enqueue a [x,y] pair

Path generation is my weakness. Needs more practice, esp. with BFT

There are three solutions presented here -- DFT, BFT and Ashish

showcase: passing test function as input to a HigherOrderFunction
'''
import sys, os, operator # locate max entry from dict
from collections import deque
from pprint import pprint
from datetime import datetime
bigMatSize=1000
if bigMatSize > 7: 
    sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)
m = list() 
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
  global m
  m.append([1,1,0,1])
  m.append([1,1,1,1])
  return 2
def startDFT(r,c, verbose): ### see comment in blog
  global finalCnt, revisits
  if len(m)*len(m[0]) > 9999: 
    print 'too large for DFT recursion'
    finalCnt = -1
    return
  addr=(r,c)

  revisits[addr] = revisits.get(addr,0)+1
  if verbose and revisits[addr] > 4: print addr, 'visited', revisits[addr], 'times :('

  if m[r][c]==0: #dead end
    return
  if r < height-1: #move down before moving right
    startDFT(r+1, c, verbose)
  if c < width-1:
    startDFT(r, c+1, verbose)
    
  if r == height-1 and c == width-1:
    finalCnt += 1 # found a path to destination
    if verbose: print 'incremented finalCnt to', finalCnt
######## BFT -- see comments in blog
class Q: #class based on collections.deque
    def __init__(self):
        self.qq = deque()
    def enQ(self, item):
        self.qq.append(item)
    def deQ(self): 
        return self.qq.popleft() # throws error if empty

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
  print 'using BFT'
  # 0 means unknown
  score=[[0 for _ in xrange(width)] for _ in xrange(height)]
  score[0][0] = 1
  q = Q()
  q.enQ((1,0))
  q.enQ((0,1))
  while q.qq:
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

def startSpreadsheet(): #Based on Ashish Singh's tips, faster than BFT
  global finalCnt, score
  score=[[0 for _ in xrange(width)] for _ in xrange(height)] # init
  for r in xrange(height): # populate first column
    if m[r][0] == 0: break # all subsequent cells in first column have score=0
    score[r][0] = 1
  for c in xrange(1,width): # populate top row
    if m[0][c] == 0: break
    score[0][c] = 1

  for r in xrange(1,height):  
    for c in xrange(1,width): 
       if m[r][c]: 
         # key insight -- there are only 2 ways to reach current node: from above or from left node. My score = score(aboveNode) + score(leftNode)
         score[r][c] = score[r-1][c] + score[r][c-1]   
  finalCnt = score[-1][-1]
def work(setup1test):
  global m, width, height, finalCnt, revisits
  m = list()
  exp = setup1test()
  height, width = len(m), len(m[0])
  finalCnt=0
  revisits=dict()
  
  if 1>2: 
    startSpreadsheet()
  else:
    verbose = (height * width < 99999)
    startBFT(verbose)  
    #startDFT(0,0, verbose)
  
  if revisits: 
    print 'most revisited node is ', max(revisits.iteritems(), key=operator.itemgetter(1))
  print '-----------> finalCnt =', finalCnt
  if finalCnt >= 0: assert exp == finalCnt%100000000000
def main():
  work(test1)
  work(test2)
  work(test3)
  work(test4)
  
  startTime=datetime.now()
  work(test9)
  print (datetime.now()-startTime).total_seconds(), 'seconds'
  work(test9b)
main()
''' Req: https://bintanvictor.wordpress.com/2018/05/28/count-paths-between-2-tree-nodes/
'''
