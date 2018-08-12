'''todo: add more tests
todo: simplify
todo: revisit accounting
todo: move the bound check into bft

key idea: deal with cycles in graph BFT

showcase: BFT with levels for shortest path
'''
from collections import deque
from pprint import pprint
from datetime import datetime
bigMatSize=1000
marker=[None,0]

def dump(q):
  for r in xrange(q.height):
    for c in xrange(q.width):
      print q.m[r][c],
    print 
  print q.start, '->', q.dest
def makeMat1():
  m=list()
  m.append([1,1,0,1])
  m.append([0,1,1,1])
  m.append([1,0,1,1])
  return m  
def test1():
  assert 3 == startBFT(Q(makeMat1(), [[0,1], [1,3]]))
  assert 5 == startBFT(Q(makeMat1(), [[0,3], [0,0]]))  
  assert 0 == startBFT(Q(makeMat1(), [[0,3], [2,0]]))
class Q: #class based on collections.deque
    def __init__(self, m, twoEnds):
        self.list = deque()
        self.m=m
        self.height=len(m)
        self.width =len(m[0])
        self.start=twoEnds[0]
        self.dest=twoEnds[1]
        self.revisits = dict()
    def enQ(self, item):
        if item[0] is not None:
          r,c=item
          if r<0 or c<0: return
          if r>=self.height or c>=self.width: return
        self.list.append(item)
    def deQ(self): 
        return self.list.popleft() # throws error if empty
def read(r,c, q, verbose=1):
  '''Created for revisit accounting, which hurts performance. 
  Comment out next line after verifying revisits.  
  '''
  if verbose: 
    addr=(r,c); q.revisits[addr] = q.revisits.get(addr, 0) + 1  
    assert r>=0 and c>=0
  return q.m[r][c]
def startBFT(q): 
  global finalCnt, score
  dump(q)
  q.enQ(q.start)
  q.enQ(marker)
  steps=0
  while(q.list):
    r,c = cell = q.deQ()
    if cell == marker:
      if not q.list: break
      q.enQ(marker)
      print 'marker rotated to end of', q.list
      steps += 1
      continue
    if read(r,c,q) != 1: continue
    print 'visiting', cell
    if cell == q.dest: 
      print 'returning', steps
      return steps
    q.m[r][c]=2
    q.enQ([r-1, c])
    q.enQ([r+1, c])
    q.enQ([r, c-1])
    q.enQ([r, c+1])
  print '   :( unconnected :('; return 0
def main():
  test1()
  return
  startTime=datetime.now()
  #work(test9)
  print (datetime.now()-startTime).total_seconds(), 'seconds'
  #work(test9b)
main()
''' Req: https://bintanvictor.wordpress.com/2018/08/11/check-2-matrix-nodes-are-connected/
    def clear(self):
      return
      del self.m[:]
      del self.twoEnds[:]
'''
