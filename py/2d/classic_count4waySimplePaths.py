'''
todo:
key idea:
showcase:
'''
class Q: #designed for BFT but useful for DFT
    def __init__(self, m, twoEnds):
        #self.list = deque()
        self.m=m
        self.height=len(m)
        self.width =len(m[0])
        self.dest=twoEnds.pop()
        self.start=twoEnds.pop()
        #self.revisits = dict()
    def __str__(self):
      ret=''
      for r in xrange(self.height):
        for c in xrange(self.width):
          ret += str(self.m[r][c])+' '
        ret +='\n'
      ret += str(self.start) + ' <----==========----> ' +str(self.dest) # both direction should give same result    
      return ret
def mat1():
  m=list() # create a new editable matrix each time
  m.append([1,1,1,1])
  m.append([0,1,0,1])
  m.append([0,1,1,1])
  m.append([1,0,1,0])
  return m
def test1():
  assert startDFT(Q(mat1(), [[0,1], [0,0]]))==1
  #assert startDFT(Q(mat1(), [[1,1], [0,0]]))==2
  #assert startDFT(Q(mat1(), [[0,3], [3,0]]))==0
def startDFT(q): #return # of simple paths
  return 1  
def main(): 
  test1()
main()
'''Req:my blog https://wp.me/p74oew-603
given 2 nodes in a C by R matrix grid, where every node is connected to (up to) four neighbors, generate all cycle-free paths.
'''
