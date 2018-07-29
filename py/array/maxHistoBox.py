'''
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
    
def largestRectangleArea(heights):
  if 'helps Notepad++folding':
    di=dict()
    for h in heights:
      assert h > 0
      di[h]= RunRecord(h)
    tree=[ di[key] for key in sorted(di.iterkeys())]
    #print tree # sorted array of non-repeating RunRecords
    
  arr=[0]
  arr.extend(heights)
  arr.append(0)
  sz=len(arr)
  # i prefer to iterate over arr, to take care of fist bar
  for i in xrange(sz-1):
    j=i+1
    assert j <= sz-1, 'j should grow to last index'
    prev= arr[i]
    cur = arr[j]
    print cur, 
    if   prev==cur:
      print 'flatline'
    elif prev< cur: 
      print 'rising'
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
           print 'updated maxRun in', rec
        rec.currentRunStart = 0
  
  # now select final winner
  ret = 0
  for rec in tree:
    area = rec.hei * rec.maxRun
    if ret < area: 
       ret = area
  return ret
def main():
  assert(10==largestRectangleArea([2,2,5,2,2]))
  assert(10==largestRectangleArea([2,1,5,6,2,3]))  
main()
'''Req:  https://bintanvictor.wordpress.com/2018/07/29/max-rectangle-histogram/

Given N (non-unique) natural numbers representing the histogram's bar heights where the width of each bar is 1, find the area of largest rectangle in the histogram.
'''