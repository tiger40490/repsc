'''
showcase defaultdict(lambda...) to easily handle negative indices
showcase passing a singe list object into izip() which expects two args
showcase deepcopy
'''
import sys
from pprint import pprint
from copy import deepcopy
from collections import defaultdict
from itertools import izip
def read(r,c): return a2[ (r,c) ] #easier to read
def bu():
  m=[['.' for _ in range(len(y))] for _ in range(len(x))]
  # Above 2D array is easy to print
  # Below defaultdict easily handles negative indices
  global a2; a2 = defaultdict(lambda: [[],[]])
  a2[(0, 0)] =  [[0],[0]] if x[0]==y[0]   else [[],[]]
  m  [0][0] = len(read(0,0))
  for r in xrange(len(x)): 
   for c in xrange(len(y)):
     #print r,c
     if len( read(r-1,c)[0] )  > len( read(r,c-1)[0] ):
       match = deepcopy(read(r-1,c))
     else:
       match = deepcopy(read(r,c-1))
     if x[r] == y[c]:
         match=deepcopy(read(r-1,c-1)) #
         match[0].append(r)
         match[1].append(c)
     a2[(r,c)] = match
     m[r][c] = len(match[0])
  for X,Y in izip(*read(r,c)): assert x[X] == y[Y]; print X, x[X], Y
  if len(m[0]) < 15: pprint(m)
  return m[r][c]
def wrapper(dirtyX,dirtyY):
  global x,y
  x = dirtyX.replace(' ','')
  y = dirtyY.replace(' ','')
  if len(y)<len(x): x,y=y,x
  for s in [x,y]:
    print ' '+('  '.join(list(s)))
    for i in range(len(s)): print '%2s' % i,  
    print '\n'
  return bu()
def main():
  assert 4==wrapper('AGGTAB', 'GXTXAYB')
  assert 3==wrapper('ABCDGH','AEDFHR')
  assert 7==wrapper('thisisatest', 'testing123testing')
  assert 10==wrapper('abbbbb-bbbbbb-a', 'aabbaabaababbabaaba')
  assert 22==wrapper('abb--bbbb-bbbb-bbbb aaaaa bbbb aaaaaa', 'aabbabbaabaabaaababababaabaababbabaaba')
main()
'''Req: longest common subsequence (not sub-string) between two strings X and Y
This is my DP solution. [[Algorithms]] P 350 also discussed a DP solution
'''