def gen(fn, pool, n):
  if n == 0: yield []; return
  for pos, ch in enumerate(pool):
    for newList in gen(fn, fn(pool,pos), n-1):
      yield [ch] + newList
	  
pool='abcde' # 2^5 abbreviations if we include "" and the original string.
def f(pool, pos):
  return pool[pos+1:]

def main():
 for length in xrange(1,len(pool)):
  for abbr in gen(f, pool, length):
    print abbr
    
# all abbr
main()
'''
Based on cookbook.py, this script was written as a practice.
'''