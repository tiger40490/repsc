'''
todo: count how many shortest paths

key idea: deal with cycles in graph BFT. No cycles if monotonic traversal in matrix
key idea: add [x,y] addresses to queue

showcase: level-aware BFT for shortest path
'''
import operator # locate max entry from dict
from collections import deque
from pprint import pprint
from datetime import datetime
marker=[None,0]

def test9():
  big=400
  def mat9():
    m = [[1 for x in xrange(big)] for y in xrange(big)]
    assert len(m) == big and len(m[0]) == big
    m[-1][0]=0
    return m
  startTime=datetime.now()
  assert big*2-2 == startBFT(Q(mat9(), [[0,0], [big-1, big-1]]))
  print (datetime.now()-startTime).total_seconds(), 'seconds. You may want to stop the remaining load tests:)'
  if big > 200: return
  assert       0 == startBFT(Q(mat9(), [[0,0], [big-1, 0]]))
def test1():
  def mat1():
    m=list()
    m.append([1,1,0,1])
    m.append([0,1,1,1])
    m.append([1,0,1,1])
    return m  
  assert 3 == startBFT(Q(mat1(), [[0,1], [1,3]]))
  assert 5 == startBFT(Q(mat1(), [[0,3], [0,0]]))  
  assert 0 == startBFT(Q(mat1(), [[0,3], [2,0]]))
class Q: #class based on collections.deque
    def __init__(self, m, twoEnds):
        self.list = deque()
        self.m=m
        self.height=len(m)
        self.width =len(m[0])
        self.dest=twoEnds.pop()
        self.start=twoEnds.pop()
        self.revisits = dict()
    def __str__(self):
      ret=''
      for r in xrange(self.height):
        for c in xrange(self.width):
          ret += str(self.m[r][c])+' '
        ret +='\n'
      ret += str(self.start) + ' <----==========----> ' +str(self.dest) # both direction should give same result    
      return ret
    def enQ(self, item):
        self.list.append(item)
    def deQ(self): 
        return self.list.popleft() # throws error if empty
def read(r,c, q, isVerbose=1):
  '''Created for revisit accounting, which hurts performance. 
  Comment out next line after verifying revisits.  
  '''
  if isVerbose: 
    addr=(r,c); q.revisits[addr] = q.revisits.get(addr, 0) + 1  
    assert r>=0 and c>=0
    assert r<q.height and c<q.width
  return q.m[r][c]
def startBFT(q): 
  global finalCnt, score
  isVerbose = (q.height*q.width < 99)
  if isVerbose: print q
  q.enQ(q.start)
  q.enQ(marker)
  steps=0
  while(q.list):
    r,c = cell = q.deQ()
    if cell == marker:
      if not q.list: break
      q.enQ(marker)
      if isVerbose: print 'marker rotated to end of', q.list
      steps += 1
      continue
    if read(r,c,q, isVerbose) != 1: continue
    if isVerbose: print 'visiting', cell
    if cell == q.dest: break
    q.m[r][c]=2
    if r > 0: q.enQ([r-1, c])
    if r < q.height-1: q.enQ([r+1, c])
    if c > 0: q.enQ([r, c-1])
    if c < q.width-1: q.enQ([r, c+1])
  if q.revisits: 
    print '\t most revisited node is ', max(q.revisits.iteritems(), key=operator.itemgetter(1))    
  if not q.list: 
    print '\t :( unconnected'; 
    return 0
  else:
    print '\t returning', steps
    return steps
def main():
  test1()
  test9()
  #work(test9b)
main()
''' Req: https://bintanvictor.wordpress.com/2018/08/11/check-2-matrix-nodes-are-connected/
'''
