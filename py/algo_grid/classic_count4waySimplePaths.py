'''
Poor scalablity -- can't handle a 6x6 matrix

key idea: deal with cycle by inspecting breadcrumb
showcase: set 
showcase: nested function to avoid passing lots of arguments
showcase: print indent to indicate recursive level
'''
import sys, operator # locate max entry from dict
from datetime import datetime

A=B=1 # helps me understand the tests
class Q: #designed for BFT but useful for DFT
  def __init__(self, m, twoEnds):
    #self.list = deque() # only needed for BFT
    self.m=m
    self.height=len(m)
    self.width =len(m[0])
    self.dest=twoEnds.pop()
    self.start=twoEnds.pop()
    self.revisits = dict()
    self.paths=set()
  def __str__(self):
    ret=''
    for r in xrange(self.height):
      for c in xrange(self.width):
        ret += str(self.m[r][c])+' '
      ret +='\n'
    ret += str(self.start) + ' <----==========----> ' +str(self.dest) # both direction should give same result    
    return ret
def test9():
  big=5 # 6x6 is overwhelming
  def mat():
    m = [[1 for _ in xrange(big)] for _ in xrange(big)]
    assert len(m) == big and len(m[0]) == big
    return m
  startTime=datetime.now()
  q = Q(mat(), [[0,0], [big-1, 0]])
  startDFT(q)
  print (datetime.now()-startTime).total_seconds(), 'seconds'
def test3():
  def mat():
    m=list() # create a new editable matrix each time
    m.append([1,1,1,1])
    m.append([0,1,0,1])
    m.append([A,0,1,1])
    m.append([1,1,1,0])
    return m  
  q = Q(mat(), [[0,0], [2,0]]) # north-west corner to A
  assert startDFT(q)==1
  import ast
  li=ast.literal_eval(list(q.paths)[0])
  assert len(li)==10, 'path length should be 10'
def test2():
  def mat():
    m=list() # create a new editable matrix each time
    m.append([1,1,1,1])
    m.append([1,1,A,1])
    m.append([0,0,1,0])
    m.append([1,0,B,0])
    return m  
  q = Q(mat(), [[0,0], [1,2]]) # A
  assert startDFT(q)==6 
  assert str([[0,0],[1,0],[1,1],[0,1],[0,2],[0,3],[1,3]]) in q.paths
  assert startDFT(Q(mat(), [[3,2], [0,0]]))==6 # B to north-west corner
def test1():
  def mat():
    m=list() # create a new editable matrix each time
    m.append([1,A,1,1])
    m.append([0,1,0,1])
    m.append([0,1,1,1])
    m.append([1,0,1,0])
    return m  
  assert startDFT(Q(mat(), [[0,1], [0,0]]))==1 # A to north-west corner
  q = Q(mat(), [[1,1], [0,0]])
  assert startDFT(q)==2
  assert str([[1,1], [2,1], [2,2], [2,3], [1,3], [0,3],[0,2],[0,1]]) in q.paths
  assert startDFT(Q(mat(), [[1,1], [2,2]]))==2
  assert startDFT(Q(mat(), [[0,3], [3,0]]))==0 # diagonal
def read(r,c, q, recursLevel, isVerbose=1):
  ret = q.m[r][c]
  if ret > 0:
    assert ret == 1
    addr=(r,c); 
    q.revisits[addr] = q.revisits.get(addr, 0) + 1  
  if isVerbose: 
    assert r>=0 and c>=0
    assert r<q.height and c<q.width
    #print '. '*(recursLevel)+str(r)+str(c),':', ret #,
  return ret
def startDFT(q): #return simple path count
  def recurs(me):
    myname = str(me)
    if myname in breadlookup: return #check cycle before checking dest
    r,c = me
    if 0 == read(r,c,q,len(breadcrumb),isVerbose): return
    if me == q.dest:
      tmp = str(breadcrumb)
      if isVerbose: print ':) path', tmp
      assert tmp not in q.paths
      q.paths.add(tmp)
      return
    breadcrumb.append(me); breadlookup.add(myname)
    assert len(breadcrumb) == len(breadlookup), 'breadcrumb has no dupes'
    if r-1 >= 0:         stat = recurs([r-1,c])
    if c+1 <= q.width-1: stat = recurs([r,c+1])
    if r+1 <=q.height-1: stat = recurs([r+1,c])
    if c-1 >= 0:         stat = recurs([r,c-1])
    breadcrumb.pop(); breadlookup.remove(myname) #throws if not in
  # end of recurs ()  
  print q
  isVerbose = (q.height*q.width < 16)
  breadcrumb = list(); breadlookup = set()
  recurs(q.start)
  if q.revisits: 
    print '\t most revisited node is ', max(q.revisits.iteritems(), key=operator.itemgetter(1))      
  print 'returning pathCnt =', len(q.paths)
  return len(q.paths)  
def main(): 
  test1()
  test2()
  test3()
  test9()
main()
'''Req:my blog https://wp.me/p74oew-603
given 2 nodes in a C by R matrix grid, where every node is connected to (up to) four neighbors, generate all cycle-free paths)
'''
