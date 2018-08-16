'''
todo: replace "remain" with a sorted "group" list derived from the list of non-unique prime factors. Each "group" is the product of any group of the non-unique prime factors

If the nupf list has xxxyyz, then there are (3+1)*(2+1)*(1+1) factors. 

'''
from math import sqrt
from operator import mul
from collections import defaultdict
cnt=0; recursionLevel=0

def primes(tgt): # simple Sieve of Eratosthenes 
   n = int(sqrt(tgt))+1 
   odds = range(3, n+1, 2)
   sieve = set(sum([range(q*q, n+1, q+q) for q in odds],[]))
   return [2] + [p for p in odds if p not in sieve]
   
def get_divisors(bigNum): # generate the non-uniq prime factors and all the partial products they could produce i.e. all the factors of bigNum
  tgt = bigNum
  p=primes(tgt) # empty list means tgt is prime
  frq = defaultdict(lambda: 0);   i=0
  while tgt > 1 and i < len(p):
    primeFac = p[i]
    if tgt%primeFac:
      i+=1
      continue
    tgt = tgt/primeFac
    frq[primeFac] += 1
  print 'nupf =', dict(frq)
  factors = [1]; checkSum=1
  for prime, cnt in frq.iteritems():
    checkSum *= (cnt+1)
    new = list()
    for i in xrange(1,cnt+1):
      for g in factors:
        new.append(g * prime**i)
    factors.extend(new)
  print len(factors), 'factors', factors
  factors = sorted(factors)
  assert factors[0] == 1
  assert factors[-1] == bigNum
  assert checkSum == len(factors)
  
  return factors[1:]
def getSmallDivisors(bigNum):
  ret = list()
  for i in get_divisors(bigNum):
    if i == 1: continue
    ret.append(i)
    if i > sqrt(bigNum): break
  return ret
      
def recurs(bigNum, remain, lowerFactors=tuple()):
  '''job: find each formula to factorize remain, but when print it, also print lowerFactors
  '''
  global cnt, recursionLevel
  if bigNum == 1: return # to optimize
  #print lowerFactors
  assert sorted(lowerFactors) == list(lowerFactors), 'should be sorted low to high'
  assert len( lowerFactors ) == recursionLevel
  recursionLevel += 1
  if lowerFactors: # i.e. non-empty
    #assert lowerFactors[-1] <= remain, 'last lowerFactors item should not exceed remain'
    cnt+=1
    _start = lowerFactors[-1] # highest existing factor -- #1 trick in this algorithm    
    print '. '*(recursionLevel-2) + str(lowerFactors), bigNum
  else: 
    print '------- factorizing', remain
    cnt=0
    _start = 2 # smallest factor in the universe    
    
  for f in remain:
    if f < _start: continue
    if bigNum % f: continue
    if lowerFactors and bigNum/f < f: break
    recurs(bigNum/f, remain, lowerFactors+(f,))
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
  factorize(36); assert(8  == cnt)
  return
  factorize(60); assert(10 == cnt)
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
