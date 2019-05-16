'''
showcase: yielding items in sorted sequence
showcase: defaultdict(int) as frequency counter
showcase: antiRepeat to avoid creating the same generator and running through it again. Without this feature, code is still correct and possibly just as fast.

todo: understand why sometimes calling gen(someValue) again gives me a different generator object?
todo: add bottom-up solution and compare performance

Unlike some DP solutions, this recursive algo can print out all paths.
Note the generator function is top-down recursive without memoization.  How to make it non-recursive? No clue
'''
from pprint import pprint
from collections import defaultdict
import time, os, sys
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0) # worked
                                         
def timeit(method):
    def timed(*args, **kw):
        ts = time.time()
        result = method(*args, **kw)
        te = time.time()
        print '%r (%r, %r) %2.2f sec' % \
              (method.__name__, args, kw, te-ts)
        return result
    return timed
uniqueGenerator=defaultdict(int)
antiRepeat=dict() #N -> list of tuples for N
def gen_memoize(n): #consistently faster than buttom_up, much faster than the simple gen()
  #print 'entering gen_memoize() with n =', n
  if n==0: yield (); return
  for i in xrange(1,n+1):
    arg = n-i
    if arg in antiRepeat:
      listOfTu = antiRepeat[arg]
    else:
      generator = gen_memoize(arg)
      #print arg, ': using generator', id(generator)
      uniqueGenerator[id(generator)] += 1
      listOfTu = list(generator)
      antiRepeat[arg] = listOfTu
    for tu in listOfTu: 
      yield (i,) + tu #concat two tuples
def gen(n): #simple generator, easy to memorize and reproduce
  if n==0: yield (); return
  for step1 in xrange(1, n+1):
    for steps in gen(n-step1):
      yield (step1,) + steps
def buttom_up(n): #produce a collection of tuples, each a formula
  ret = [ [] for i in range(n+1) ]
  ret[0] = [()] # crucial
  for height in xrange(1, n+1): 
    formulas=ret[height]; # assert id(formulas) == id(ret[height])
    for step1 in xrange(1, height+1) : #step1 can be size 1 to size height
      for path in ret[height-step1] :
        formulas.append(  (step1,) + path )
    #print 'height =',height, formulas
  return ret[n]
@timeit
def verify(n, algo):
  li = list(algo(n)); uniq = set(li)
  if n < 5: pprint(li) # all paths
  assert len(li)==len(uniq)==2**(n-1)
def test(n):
  verify(n, buttom_up)
  verify(n, gen_memoize)
  verify(n, gen)
  # now check the generators
  #print len(uniqueGenerator), 'unique generators: ', uniqueGenerator
  assert len(uniqueGenerator)==n, 'each time gen(11) is called it should return the same generator object'
  uniqueGenerator.clear(); antiRepeat.clear()
test(21) #21 ok
test(4)
'''
Req: https://bintanvictor.wordpress.com/2018/07/29/ladder-problem-csy-bbg/, which lists a c++ solution in my github
'''