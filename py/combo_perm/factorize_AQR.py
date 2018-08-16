'''
todo: replace "remain" with a sorted "group" list derived from the list of non-unique prime factors. Each "group" is the product of any group of the non-unique prime factors

todo extract to module get_divisors
'''
from math import sqrt
#from operator import mul
from collections import defaultdict
cnt=0; recursionLevel=0

def get_primes(tgt): # simple Sieve of Eratosthenes 
   n = int(sqrt(tgt))+1 
   odds = xrange(3, n+1, 2)
   sieve = set(sum([range(q*q, n+1, q+q) for q in odds],[]))
   return [2] + [p for p in odds if p not in sieve]
def get_nupf(tgt): # generate the non-unique prime factors
  allPrimes=get_primes(tgt) # empty list means tgt is prime
  frq = defaultdict(lambda: 0);   i=0
  while tgt > 1 and i < len(allPrimes):
    primeFac = allPrimes[i]
    if tgt%primeFac:
      i+=1
      continue
    tgt = tgt/primeFac
    frq[primeFac] += 1
  print 'nupf =', dict(frq)
  return frq
def get_divisors(tgt): # generate all divisors of tgt
  frq = get_nupf(tgt)
  divisors = [1]; checkSum=1
  for prime, cnt in frq.iteritems():
    checkSum *= (cnt+1)
    divisors.extend([g * prime**i for g in divisors for i in xrange(1,cnt+1)])
  print len(divisors), 'divisors', divisors
  assert checkSum == len(divisors)
  divisors = sorted(divisors)
  assert divisors[0] == 1
  assert divisors[-1] == tgt
  return divisors, frq
##### reusable functions to be extracted into module
  
def getSmallDivisors(bigNum): # to optimize away
  ret = list()
  divisors, frq = get_divisors(bigNum)
  for i in divisors:
    if i == 1: continue
    ret.append(i)
    if i > sqrt(bigNum): break
  return ret
      
def recurs(bigNum, divisors, lowerFactors=tuple()):
  global cnt, recursionLevel
  if bigNum == 1: return # to optimize away
  assert sorted(lowerFactors) == list(lowerFactors), 'should be sorted low to high'
  assert len( lowerFactors ) == recursionLevel
  recursionLevel += 1
  if lowerFactors: # i.e. non-empty
    #assert lowerFactors[-1] <= divisors, 'last lowerFactors item should not exceed divisors'
    cnt+=1
    _start = lowerFactors[-1] # highest existing factor -- #1 trick in this algorithm    
    print '. '*(recursionLevel-2) + str(lowerFactors), bigNum
  else: 
    print '------- factorizing', bigNum
    cnt=0
    _start = 2 # smallest factor in the universe    
    
  '''  for f in xrange(_start, int(sqrt(remain))+1):
    if remain%f: continue
    recursCSY(remain/f, lowerFactors+(f,))
  '''    
  for f in divisors: # scan all divisors from _start to sqrt of current bigNum
    if f < _start: continue
    if bigNum % f: continue
    if bigNum/f < f: break
    recurs(bigNum/f, divisors, lowerFactors+(f,))
  recursionLevel -= 1
def recursCSY(remain, lowerFactors=tuple()):
  '''job: find each formula to factorize remain, but when print it, also print lowerFactors
  '''
  global cnt, recursionLevel
  assert sorted(lowerFactors) == list(lowerFactors), 'should be sorted low to high'
  assert len( lowerFactors ) == recursionLevel
  recursionLevel += 1
  if lowerFactors: # i.e. non-empty
    assert lowerFactors[-1] <= remain, 'last lowerFactors item should not exceed remain'
    cnt+=1
    _start = lowerFactors[-1] # highest existing factor -- #1 trick in this algorithm
    print '. '*(recursionLevel-2) + str(lowerFactors), remain
  else: 
    print '------- factorizing', remain
    cnt=0
    _start = 2 # smallest factor in the universe
    
  # loop below is too ineffient. Should replace the xrange with the remaining "factors"
  for f in xrange(_start, int(sqrt(remain))+1):
    if remain%f: continue
    recursCSY(remain/f, lowerFactors+(f,))
  recursionLevel -= 1
def factorize(bigNum):
  recursCSY(bigNum)
  recurs(bigNum, getSmallDivisors(bigNum))
def main():
  #print get_divisors(600)
  factorize(60); assert(10 == cnt)
  factorize(36); assert(8  == cnt)
  factorize(24); assert(6  == cnt)
  factorize(12); assert(3  == cnt)
  return
  A=2; B=3; C=5; D=7
  factorize((A*C)**12) # a trillion
  factorize(A**10 * B**8 * C**6 * D**4) # need to use q(python -u)
main()
'''Requirement: https://bintanvictor.wordpress.com/2017/04/16/factorize-a-natural-number-aqr/
--for 36 we want
fac 36 () iterating from 2 to 6
  fac 18 (+2) iterating from 2 to 4
    fac 9 (2, +2)
      fac 3 (2,2, +3)
    fac 6 (2, +3)
  fac 12 (+3) iterating from 3 to 3
    fac 4 (3, +3)
  fac 9 (+4) # when factorizing 9, we ignore factors below 4, since they are taken care of in an earlier recursive call
  fac 6 (+6)
'''
