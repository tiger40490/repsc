'''
showcase
todo: sort objects by a field
'''
from pprint import pprint
class Rec(object): #RunRecord
  NO_CURRENT_RUN = '-'
  def __init__(self, hei, currentRunStart=NO_CURRENT_RUN):
    self.hei=hei
    self.maxRun=0
    
    # crs is 1-based, not 0-based
    self.crs=currentRunStart #'-' to indicate no current run
  def __str__(self):
    return str(self.hei)+"->"+str(self.maxRun)+'|'+str(self.crs)
  def __repr__(self):
    return self.__str__()
    
def largestRectangleArea(heights):
  if 'helps Notepad++folding':
    di=dict()
    for h in heights:
      assert h > 0
      di[h]= Rec(h)
    tree=[ di[key] for key in sorted(di.iterkeys())] 
    #print tree # sorted array of non-repeating RunRecords
    
  arr=[0]
  arr.extend(heights)
  arr.append(0)
  szh=len(heights)
  sza=len(arr)
  # i prefer to iterate over arr, to take care of fist bar
  for i in xrange(sza-1):
    j=i+1
    assert j <= sza-1, 'j should grow to last index'
    prev= arr[i]
    cur = arr[j]
    print cur, 
    if   arr[i]==arr[j]:
      print 'flatline'
    elif arr[i]< arr[j]: 
      print 'rising'
      for rec in tree: # iterate from prev +1 to cur
        if rec.hei <= prev: 
          assert rec.crs > 0
          continue 
        if rec.hei > cur: break
        rec.crs = j
        print 'started a run in', rec
    elif arr[i]> arr[j]:
      print 'falling'
    else:
      assert 1==2, 'should never reach here'
  
  return 10
def main():
  assert(10==largestRectangleArea([2,1,5,6,2,3]))
main()
'''Req:  https://bintanvictor.wordpress.com/2018/07/29/max-rectangle-histogram/

Given N (non-unique) natural numbers representing the histogram's bar heights where the width of each bar is 1, find the area of largest rectangle in the histogram.
'''