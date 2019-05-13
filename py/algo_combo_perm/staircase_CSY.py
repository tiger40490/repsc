'''
showcase: yielding items in sorted sequence
showcase: defaultdict(int) as frequency counter

todo: understand why sometimes calling gen(someValue) again gives me a different generator object?
Note the generator function is top-down recursive without memoization.  How to make it non-recursive? No clue
'''
from pprint import pprint
from collections import defaultdict
uniqueGenerator=defaultdict(int)
def gen(n):
  #print 'entering gen() with n =', n
  if n==0: yield (); return
  for i in xrange(1,n+1):
    generator = gen(n-i)
    #print 'using generator', generator
    uniqueGenerator[id(generator)] += 1
    for tu in generator: 
      yield (i,) + tu #concat two tuples
def test(n):
  li = list(gen(n))
  uniq = set(li)
  pprint(li)
  print len(uniqueGenerator), 'unique generators: ', uniqueGenerator
  #assert len(uniqueGenerator)==n, 'each time gen(11) is called it should return the same generator object'
  uniqueGenerator.clear()
  assert len(li)==len(uniq)==2**(n-1)
test(8)
test(4)
'''
Req: https://bintanvictor.wordpress.com/2018/07/29/ladder-problem-csy-bbg/, which lists a c++ solution in my github
'''