'''
showcase defaultdict(lambda...) to easily handle negative indices into a matrix
showcase passing a singe list object into izip() which expects two args
showcase deepcopy
'''
import sys
from pprint import pprint
from copy import deepcopy
from collections import defaultdict
from itertools import izip
def read(r,c): return a2[ (r,c) ] #easier to read
def botup(isVerbose=False):
  m=[['.' for _ in range(len(y))] for _ in range(len(x))]
  # Above 2D array is easy to print. m[r][c] is the length of lcs between x[:r] and y[:c]
  # Below defaultdict easily handles negative indices. I think a2 was designed for instrumentation. The dict value is list of index pairs
  global a2; a2 = defaultdict(lambda: [])
  a2[(0, 0)] =  [[0,0]] if x[0]==y[0]   else []
  m  [0][0] =         1 if x[0]==y[0]   else 0
  for r in xrange(len(x)): 
   for c in xrange(len(y)):
     if isVerbose: print r,c
     if len( read(r-1,c) )  > len( read(r,c-1) ):
       match = deepcopy(read(r-1,c))
     else:
       match = deepcopy(read(r,c-1))
     if x[r] == y[c]:
         match=deepcopy(read(r-1,c-1)) #
         match.append([r,c])
     a2[(r,c)] = match
     
     if isVerbose:
       print a2[(r,c)]
       for X,Y in read(r,c): assert x[X] == y[Y]
     m[r][c] = len(match)
  # game over. Now print result
  print 'x    y <-- idx into both strings\n------'
  for X,Y in read(r,c): assert x[X] == y[Y]; print "%2d"%X, x[X], Y
  if len(m[0]) < 15: pprint(m)
  return m[r][c]
def wrapper(dirtyX,dirtyY):
  global x,y
  x = dirtyX.replace(' ','')
  y = dirtyY.replace(' ','')
  if len(y)<len(x): x,y=y,x #ensure x is the shorter string
  for s in [x,y]:
    print ' '+('  '.join(list(s)))
    for i in range(len(s)): print '%2s' % i,  
    print '\n'
  return botup()
def main():
  assert 4==wrapper('AGGTAB', 'GXTXAYB')
  #return
  assert 3==wrapper('ABCDGH','AEDFHR')
  assert 7==wrapper('thisisatest', 'testing123testing')
  assert 10==wrapper('abbbbb-bbbbbb-a', 'aabbaabaababbabaaba')
  assert 22==wrapper('abb--bbbb-bbbb-bbbb aaaaa bbbb aaaaaa', 'aabbabbaabaabaaababababaabaababbabaaba')
main()
'''Req: longest common subsequence (not sub-string) between two strings X and Y
This is my DP solution. [[Algorithms]] P 350 also discussed a DP solution
https://bintanvictor.wordpress.com/wp-admin/post.php?post=29740&action=edit
'''