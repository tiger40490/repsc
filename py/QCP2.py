'''
One big pitfall is the one-based vs zero-based. I need clear and short var names. Every time we look up in array, we must use zero-based, but input/output is always dateId, i.e. one-based.

winner var is a list. Can be a scalar in this problem, but in general, a list is versatile as a global var as it can be updated/overwritten without "global winner"

Q: should initialize winner with the default return value of -1? 
A: often a good simplification, but not in this case. This is an important observation, an important question in speed coding
A: using -1 would give too many responsibilities to the default value. Very hard to manage. Instead, separate variables should take up those responsibilities depending on the algorithm design.
'''
import sys
def predictAnswer(stockData, queries):
  ret = list()
  for date in queries:
    nearestDate = query1(stockData, date)
    ret.append( nearestDate )
  return ret

def query1(stockData, date):
  pos = date-1 # "i" is already in use. I could use pos. "idx" is too similar to "i"
  
  winner = [sys.maxint]
  for i,v in enumerate(stockData):
    #print i,v
    if v >= stockData[pos]: continue
    dist = pos - i
    print i,v, 'dist=', dist
    if abs(dist) < abs(winner[0]-pos): # if two candidates tie, then the earlier day wins and we don't enter here. 
    # This is by design, since we scan from left
      print "new winner", i, v
      winner = [i]
  if winner[0] == sys.maxint: return -1
  return winner[0]+1

assert predictAnswer([5,6,8,4,9,10,8,3,6,4], [3,1,8]) == [2,4,-1]
'''Req: You have a time-series of daily prices. The array-index is dateId-1.
For each target dateId, find the nearest dateId when price is strictly lower than the target. 

If none, return -1

If tie, then return the earliest.
'''