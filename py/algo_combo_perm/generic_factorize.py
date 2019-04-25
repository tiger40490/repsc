from math import sqrt
from collections import defaultdict

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
  assert checkSum == len(divisors)
  divisors = sorted(divisors)
  assert divisors[0] == 1
  assert divisors[-1] == tgt
  print len(divisors), 'divisors', divisors
  return divisors[1:], frq
##### reusable functions to be extracted into module
