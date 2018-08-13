'''
todo: populate a global collection of  and verify that
todo: add more complex tests
todo: simplify
todo: tuning
todo: check revisits
key idea:
showcase: print indent to indicate recursive level
'''
import sys
A=B=1 # helps me understand the tests
class Q: #designed for BFT but useful for DFT
  def __init__(self, m, twoEnds):
    #self.list = deque()
    self.m=m
    self.height=len(m)
    self.width =len(m[0])
    self.dest=twoEnds.pop()
    self.start=twoEnds.pop()
    self.revisits = dict()
    self.pathCnt=0
    self.paths=set()
  def __str__(self):
    ret=''
    for r in xrange(self.height):
      for c in xrange(self.width):
        ret += str(self.m[r][c])+' '
      ret +='\n'
    ret += str(self.start) + ' <----==========----> ' +str(self.dest) # both direction should give same result    
    return ret
def test2():
  def mat():
    m=list() # create a new editable matrix each time
    m.append([1,1,1,1])
    m.append([1,1,A,1])
    m.append([0,0,1,0])
    m.append([1,0,B,0])
    return m  
  assert startDFT(Q(mat(), [[1,2], [0,0]]))==6 # A
  assert startDFT(Q(mat(), [[3,2], [0,0]]))==6 # B
def test1():
  def mat():
    m=list() # create a new editable matrix each time
    m.append([1,A,1,1])
    m.append([0,1,0,1])
    m.append([0,1,1,1])
    m.append([1,0,1,0])
    return m  
  assert startDFT(Q(mat(), [[0,1], [0,0]]))==1 # Node A
  q = Q(mat(), [[1,1], [0,0]])
  assert startDFT(q)==2
  assert str([[1,1], [2,1], [2,2], [2,3], [1,3], [0,3],[0,2],[0,1]]) in q.paths
  assert startDFT(Q(mat(), [[1,1], [2,2]]))==2
  assert startDFT(Q(mat(), [[0,3], [3,0]]))==0 # diagonal
def read(r,c, q, recursLevel, isVerbose=1):
  ret = q.m[r][c]
  if ret > 0:
    addr=(r,c); 
    tmp = q.revisits[addr] = q.revisits.get(addr, 0) + 1  
    assert ret == 1
  if isVerbose: 
    assert r>=0 and c>=0
    assert r<q.height and c<q.width
    #print '. '*(recursLevel)+str(r)+str(c),':', ret #,
  return ret
def startDFT(q): #return # of simple paths
  def recurs(me, ancestors):
    '''ancestor does not include me
    '''
    if me in ancestors: return #check this before checking dest
    r,c = me
    val = read(r,c,q,len(ancestors),isVerbose)
    #print ancestors
    if 0 == val: return # 0
    if me == q.dest:
      print '\t\t:) path found', ancestors
      q.pathCnt += 1
      q.paths.add(str(ancestors))
      return #999
    ancestors.append(me)
    if r-1 >= 0: 
      stat = recurs([r-1,c], ancestors)
    if c+1 <= q.width-1:   
      stat = recurs([r,c+1], ancestors)
    if r+1 <= q.height-1:  
      stat = recurs([r+1,c], ancestors)
    if c-1 >= 0:  
      stat = recurs([r,c-1], ancestors)
    ancestors.pop()
  # end of recurs  
  print q
  isVerbose = (q.height*q.width < 99)
  recurs(q.start, list())
  assert len(q.paths) == q.pathCnt
  print 'returning pathCnt =', q.pathCnt
  return q.pathCnt  
def main(): 
  test1()
  test2()
main()
'''Req:my blog https://wp.me/p74oew-603
given 2 nodes in a C by R matrix grid, where every node is connected to (up to) four neighbors, generate all cycle-free paths.

from NodeA start a trail with an empty lookup hashtable to hold brown i.e. visited nodes. We can't revisit any node already visited on current trail
if this is a matrix, then instead of a hashtable, we can also use a shadow matrix, but how do we efficiently clear it before the next trail?
if we can reach a node surrounded by brown nodes, then the trail fails
else we will reach NodeB :)
Print the path.. I would say each recurs(ancestors as a vector)
'''
