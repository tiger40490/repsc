'''
showcase inserting element at front of a list
showcase assign 2 adjacent list slements to 2 scalar variables
showcase __repr__ using __str__ to support pprint
'''
class RunRecord(object): #RunRecord
  def __init__(self, hei):
    self.hei=hei
    self.maxRun=0
    
    # currentRunStart is 1-based, not 0-based
    self.currentRunStart=0 # 0 to indicate no current run
  def __str__(self):
    return str(self.hei)+":"+str(self.maxRun)+'!'+str(self.currentRunStart)
  def __repr__(self):
    return self.__str__()
    
def binsearch(tree, hei): # returns the tree index matching hei, or throw exception
  print 'binsearch() for', hei
  if hei <= 0: return 0
  ret = le = 0; ri = len(tree)-1
  while le < ri: 
    ret = (le+ri)/2
    print 'trying', ret
    if tree[ret].hei == hei: 
      print 'returning', ret
      return ret
    if tree[ret].hei >  hei: ri = ret
    else: le = ret
  assert 1==2, 'needle not found'
    
def largestRectangleArea(heights):
  if 'helps Notepad++folding':
    di=dict()
    for i in xrange(len(heights)):
      heights[i] += 1
      h = heights[i]
      assert h > 0
      di[h]= RunRecord(h)
    tree=[ di[key] for key in sorted(di.iterkeys())]
    #print tree # sorted array of non-repeating RunRecords
    
  arr=[0] + heights + [0]
  print '======= raised and extended bars =', arr
  sz=len(arr)
  for i in xrange(sz-1):
    j=i+1
    assert j <= sz-1, 'j should grow to last index'
    prev,cur= arr[i:i+2]
    print cur, 
    if   prev==cur: 
      print 'flatline'
    elif prev< cur: 
      print 'rising'
      #for i in xrange(binsearch(tree, prev)+1, len(tree)):
        #rec = tree[i] # iterate from prev +1 to cur
        #assert rec.hei > prev
      for rec in tree: # iterate from prev +1 to cur
        if rec.hei <= prev: 
          assert rec.currentRunStart > 0
          continue 
        if rec.hei > cur: break
        rec.currentRunStart = j
        print 'started a run in', rec
    else:
      assert prev> cur
      print 'falling'
      for rec in tree: # iterate from cur+1 to prev
        if rec.hei <= cur:
          assert rec.currentRunStart > 0
          continue
        if rec.hei > prev: break
        #print 'updating', rec
        # end the current run, update maxRun
        lastRun = j - rec.currentRunStart
        if rec.maxRun < lastRun: 
           rec.maxRun = lastRun
           #print 'updated maxRun in', rec
        rec.currentRunStart = 0
  
  # now select final winner
  ret = 0
  for rec in tree:
    area = (rec.hei-1) * rec.maxRun
    if ret < area: 
       ret = area
  return ret
def main():
  #largestRectangleArea(range(19999))
  assert(9==largestRectangleArea([0,9]))
  assert(10==largestRectangleArea([2,2,5,2,2]))
  assert(10==largestRectangleArea([2,1,5,6,2,3]))  
main()
'''Req:  https://bintanvictor.wordpress.com/2018/07/29/max-rectangle-histogram/
'''