'''todo: 
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
    
def binsearch(sortedRecords, hei): # to compensate for lack of treemap
  #print 'binsearch() for', hei
  if hei == 0: return -1 # not a real hit
  hit = le = 0; ri = len(sortedRecords)-1
  while le < ri: 
    hit = (le+ri)/2
    #print 'trying', hit
    if sortedRecords[hit].hei == hei: 
      #print 'returning hit =', hit
      return hit
    if sortedRecords[hit].hei >  hei: ri = hit
    else: le = hit
  assert 1==2, 'needle not found'
    
def largestRectangleArea(heights):
  if 'helps Notepad++folding':
    di=dict()
    for i in xrange(len(heights)):
      heights[i] += 1
      h = heights[i]
      assert h > 0
      di[h]= RunRecord(h)
    sortedRecords=[ di[key] for key in sorted(di.iterkeys())]
    
  arr=[0] + heights + [0]
  sz=len(arr)
  dbg = sz < 9
  if dbg:
    print '======= raised and extended bars =', arr
    print sortedRecords # sorted array of non-repeating RunRecords
  for i in xrange(sz-1):
    j=i+1
    assert j <= sz-1, 'j should grow to last index'
    prev,cur= arr[i:i+2]
    if dbg: print cur, 
    if   prev==cur: 
      if dbg: print 'flatline'
    elif prev< cur: 
      if dbg: print 'rising'
      for i in xrange(binsearch(sortedRecords,prev)+1, len(sortedRecords)):
        rec = sortedRecords[i] # iterate from prev +1 to cur
        assert rec.hei > prev
        if rec.hei > cur: break
        rec.currentRunStart = j
        #print 'started a run in', rec
    else:
      assert prev> cur
      if dbg: print 'falling'
      for i in xrange(binsearch(sortedRecords,cur)+1, len(sortedRecords)):
        rec = sortedRecords[i] # iterate from cur+1 to prev
        if rec.hei > prev: break
        #print 'updating', rec
        lastRun = j - rec.currentRunStart
        if rec.maxRun < lastRun: 
           rec.maxRun = lastRun
           #print 'updated maxRun in', rec
        rec.currentRunStart = 0
  # now select final winner
  ret = 0
  for rec in sortedRecords:
    area = (rec.hei-1) * rec.maxRun
    if ret < area: 
       ret = area
  return ret
def main():
  largestRectangleArea(range(19999))
  assert(9==largestRectangleArea([0,9]))
  assert(10==largestRectangleArea([2,2,5,2,2]))
  assert(10==largestRectangleArea([2,1,5,6,2,3]))  
main()
'''Req:  https://bintanvictor.wordpress.com/2018/07/29/max-rectangle-histogram/
'''