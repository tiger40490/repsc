'''
'''
from collections import defaultdict
subSum=defaultdict(int)
def gen(fn, pool, n):
  if n == 0: yield (); return
  for pos, ch in enumerate(pool):
    for smallTuple in gen(fn, fn(pool,pos), n-1):
      new = (ch,) + smallTuple
      #print smallTuple, '->', new
      if new not in subSum:
        subSum[new] = subSum[smallTuple] + int(ch,16)
      yield new
	  
pool='0123a' # 2^5 abbreviations if we include "" and the original string.
def f(pool, pos):
  return pool[pos+1:]

def allAbbr():
 for length in xrange(1,len(pool)):
  print '  vvvvvvvvvvv  length =', length
  for abbr in gen(f, pool, length):
    print abbr, '-- sum =', subSum[abbr]
    
allAbbr()
'''
Based on cookbook.py, this script was written as a practice.
Now I think this way of generating 2^N -2 abbreviations is worse than O(2^N).
'''