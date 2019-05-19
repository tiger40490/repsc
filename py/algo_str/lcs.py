'''
todo: shorten
todo: check if deepcopy needed

showcase passing a singe list object into izip() which expects two args
'''
from pprint import pprint
from copy import deepcopy
from collections import defaultdict
from itertools import izip
def read(r,c): return a2[ (r,c) ] #easier to read
def bu():
  global m; m=[['.' for _ in range(len(y))] for _ in range(len(x))]
  global a2; 
  a2 = defaultdict(lambda: [[],[]])
  a2[(0, 0)] =  [[0],[0]] if x[0]==y[0]   else [[],[]]
  m  [0][0] = len(read(0,0))
  for r in xrange(len(x)): 
   for c in xrange(len(y)):
     #print r,c
     if len( read(r-1,c)[0] )  > len( read(r,c-1)[0] ):
       det = deepcopy(read(r-1,c))
     else:
       det = deepcopy(read(r,c-1))
     if x[r] == y[c]:
         det=deepcopy(read(r-1,c-1)) #
         #det=read(r-1,c-1) #working?
         det[0].append(r)
         det[1].append(c)
     a2[(r,c)] = det
     m[r][c] = len(det[0])
  for X,Y in izip(*read(r,c)): assert x[X] == y[Y]; print X, x[X], Y
  pprint(m)
  return m[r][c]
def cleanup(dirtyX,dirtyY):
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
  assert 10==cleanup('abbbbb-bbbbbb-a', 'aabbaabaababbabaaba')
  assert 4==cleanup('AGGTAB', 'GXTXAYB')
  assert 3==cleanup('ABCDGH','AEDFHR')
  assert 7==cleanup('thisisatest', 'testing123testing')
main()
'''Req: longest common subsequence (not sub-string) between two strings X and Y
'''