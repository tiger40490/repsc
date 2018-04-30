from math import sqrt
cnt=0; recursionLevel=0
def factorize(tgt, smallFactors=tuple()):
  '''find each formula to factorize tgt, but when print it, also print smallFactors
  '''
  global cnt, recursionLevel
  assert sorted(smallFactors) == list(smallFactors), 'should be sorted low to high'
  assert len( smallFactors ) == recursionLevel
  recursionLevel += 1
  if smallFactors: # i.e. non-empty
    assert smallFactors[-1] <= tgt
    cnt+=1
    _start = smallFactors[-1] # highest existing factor
    print smallFactors, tgt
  else: 
    cnt=0
    _start = 2
    print '------- factorizing', tgt
  for f in xrange(_start, int(sqrt(tgt))+1):
    if tgt%f: continue
    factorize(tgt/f, smallFactors+(f,))
  recursionLevel -= 1
  return cnt

def main():
  assert(8  == factorize(36));
  #return
  assert(10 == factorize(60));
  assert(6  == factorize(24));
  assert(3  == factorize(12));  
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
