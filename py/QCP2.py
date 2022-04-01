# Need to pre-process
import math, sys
def predictAnswer(stockData, queries):
  ret = list()
  for q in queries:
    ret.append( do1(stockData, q))
  return ret
def do1(stockData, q):
  pos = q-1
  winner = [sys.maxint] #default return value???
  for i,v in enumerate(stockData):
    #print i,v
    if v >= stockData[pos]: continue # discard all days above
    dist = pos - i
    #print i,v, 'dist=', dist
    if abs(dist) < abs(pos-winner[0]): # if two candidates, then the earlier day wins
      #print "new winner", i, v
      winner = [i]
  if winner[0] == sys.maxint: return -1
  return winner[0]+1

#print predictAnswer([5,6,8,4,9,10,8,3,6,4], [3,1,8])
print predictAnswer([5,6,8,4,9,10,8,3,6,4], [6])