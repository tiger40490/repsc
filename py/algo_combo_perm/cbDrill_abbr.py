'''
todo: print the list but also a "list sum". Use a lookup table.
'''
subSum=dict()
def gen(fn, pool, n):
  if n == 0: yield (); return
  for pos, ch in enumerate(pool):
    for newList in gen(fn, fn(pool,pos), n-1):
      new = (ch,) + newList
      # compute list sum based on list sum of newList
      print newList, '->', new
      subSum[new] = subSum.get(newList, 0) + int(ch,16)
      yield new
	  
pool='0123a' # 2^5 abbreviations if we include "" and the original string.
def f(pool, pos):
  return pool[pos+1:]

def main():
 for length in xrange(1,len(pool)):
  print '  vvvvvvvvvvv  length =', length
  for abbr in gen(f, pool, length):
    print abbr, '-- sum =', subSum[abbr]
    
# all abbr
main()
'''
Based on cookbook.py, this script was written as a practice.
Now I think this way of generating 2^N -2 abbreviations has worse time complexity than O(2^N).
'''