#todo: early exit when no path
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
def test3():
  global m
  m.append([1,1,0,1])
  m.append([0,0,1,1])
  m.append([1,1,1,1])
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
class Q: #class based on deque
    def __init__(self):
        self.list = deque()
    def enQ(self, item):
        self.list.append(item)
    def deQ(self): 
        return self.list.popleft() # throws error if empty

score=list() 

def readScore(r,c):
  '''Created for revisit accounting, which hurts performance. 
  Comment out next line after verifying revisits.  
  '''
  addr=(r,c); revisits[addr] = revisits.get(addr, 0) + 1  
  return score[r][c]
def startBFT(verbose=1): 
  global finalCnt, score
  # 0 means unknown; None means unreachable though I don't use None for now
  score=[[0 for x in xrange(width)] for y in xrange(height)]
  score[0][0] = 1
  q = Q()
  q.enQ((1,0))
  q.enQ((0,1))
  while q.list:
    r,c = q.deQ()
    if m[r][c] == 0: continue
    if readScore(r,c) > 0: continue # See Keynote in blog
    tmp  = readScore(r-1, c) if r>0 else 0
    tmp += readScore(r, c-1) if c>0 else 0
    assert tmp > 0
    score[r][c] = tmp # if tmp > 0 else None
    if verbose: print r,c,' --> score set to ', score[r][c]   
    #if tmp == 0: continue # current node is unreachable   
    if r < height-1 : 
        q.enQ((r+1, c))
    if c < width-1 :
        q.enQ((r, c+1))
  finalCnt = score[-1][-1]

def startSpreadsheet(): #Based on Ashish Singh's tips
  global finalCnt, score
  score=[[0 for x in xrange(width)] for y in xrange(height)] # init
  
  for r in xrange(height): # populate left-nost column
    if m[r][0] == 0: 
      break
    score[r][0] = m[r][0]
  for c in xrange(1,width): # populate top row
    if m[0][c] == 0: 
      break
    score[0][c] = m[0][c]
  # all top and left boundary cells have scores 1 (unless blocked) since for each cell there's only one path from origin.
  for r in xrange(1,height):  
    for c in xrange(1,width): 
       if m[r][c]: 
         score[r][c] = score[r-1][c] + score[r][c-1]   
  finalCnt = score[-1][-1]
def work(setup1test, verbose=1):
  global m, width, height, finalCnt, revisits
  m = list()
  setup1test()
  height, width = len(m), len(m[0])
  assert m[0][0] == m[-1][-1] == 1
  finalCnt=0
  revisits=dict()
  
  if 1>2: 
    startSpreadsheet()
  else:
    startBFT(verbose)  
    #startDFT(0,0, verbose)
  if revisits: 
    print 'most revisited node is ', max(revisits.iteritems(), key=operator.itemgetter(1))
  print '-----------> finalCnt =', finalCnt
def main():
  work(test1)
  work(test2)
  work(test3)
  
  startTime=datetime.now()
  work(test9, verbose=0)
  print (datetime.now()-startTime).total_seconds(), 'seconds'

main()
''' Req: https://bintanvictor.wordpress.com/2018/05/28/count-paths-between-2-tree-nodes/
'''
