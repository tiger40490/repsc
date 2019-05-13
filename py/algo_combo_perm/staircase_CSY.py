'''
showcase: yielding items in sorted sequence
Note the generator function is recursive.  How to make it non-recursive? No clue
'''
from pprint import pprint
def gen(n):
  if n==0: yield (); return
  for i in xrange(1,n+1):
    for tu in gen(n-i): 
      yield (i,) + tu #concat two tuples
def test(n):
  li = list(gen(n))
  uniq = set(li)
  pprint (li)
  assert len(li)==len(uniq)==2**(n-1)
test(4)
test(7)
'''
Req: https://bintanvictor.wordpress.com/2018/07/29/ladder-problem-csy-bbg/, which lists a c++ solution in my github
'''