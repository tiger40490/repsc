'''
showcase: yielding items in sorted sequence
showcase: defaultdict(int) as frequency counter

todo: understand why sometimes calling gen(someValue) again gives me a different generator object?
Note the generator function is top-down recursive without memoization.  How to make it non-recursive? No clue
'''
from pprint import pprint
from collections import defaultdict
uniqueGenerator=defaultdict(int)
antiRepeat=dict() #N -> list of tuples for N
def gen(n):
  #print 'entering gen() with n =', n
  if n==0: yield (); return
  for i in xrange(1,n+1):
    arg = n-i
    if arg in antiRepeat:
      listOfTu = antiRepeat[arg]
    else:
      generator = gen(arg)
      print arg, ': using generator', id(generator)
      uniqueGenerator[id(generator)] += 1
      listOfTu = list(generator)
      antiRepeat[arg] = listOfTu
    for tu in listOfTu: 
      yield (i,) + tu #concat two tuples
def test(n):
  li = list(gen(n))
  uniq = set(li)
  #pprint(li)
  print len(uniqueGenerator), 'unique generators: ', uniqueGenerator
  assert len(uniqueGenerator)==n, 'each time gen(11) is called it should return the same generator object'
  uniqueGenerator.clear()
  antiRepeat.clear()
  assert len(li)==len(uniq)==2**(n-1)
test(13)
test(4)
'''
Req: https://bintanvictor.wordpress.com/2018/07/29/ladder-problem-csy-bbg/, which lists a c++ solution in my github
'''