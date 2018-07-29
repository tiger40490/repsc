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
    self.crs=currentRunStart #'-' to indicate no current run
  def __str__(self):
    return str(self.hei)+"->"+str(self.maxRun)+'|'+str(self.crs)
  def __repr__(self):
    return self.__str__()
    
def largestRectangleArea(heights):
  if 1: # helps Notepad++ folding
    di=dict()
    for h in heights:
      assert h > 0
      di[h]= Rec(h)
    tree=[ di[key] for key in sorted(di.iterkeys())] 
    print tree # sorted array of non-repeating RunRecords
  
  return 10
def main():
  
  assert(10==largestRectangleArea([2,1,5,6,2,3]))
main()
'''Req:  https://bintanvictor.wordpress.com/2018/07/29/max-rectangle-histogram/

Given N (non-unique) natural numbers representing the histogram's bar heights where the width of each bar is 1, find the area of largest rectangle in the histogram.
'''