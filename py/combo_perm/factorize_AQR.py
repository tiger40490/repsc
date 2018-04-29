from math import sqrt
#smallFactors is sorted from low to high
cnt=0
def factorize(bigNum, smallFactors=tuple()):
  '''find each formula to factorize bigNum, but when print it, also print smallFactors
  '''
  print smallFactors, bigNum
  global cnt
  if smallFactors: cnt+=1
  else: cnt=0
  tmp = smallFactors[-1] if smallFactors else 2 #highest existing factor
  for f in xrange(tmp, int(sqrt(bigNum))+1):
    if bigNum%f: continue
    factorize(bigNum/f, smallFactors + (f,))
  return cnt

def main():
  assert(8  == factorize(36));
  #return
  assert(10 == factorize(60));
  assert(6  == factorize(24));
  assert(3  == factorize(12));  
main()
'''Requirement: https://bintanvictor.wordpress.com/2017/04/16/factorize-a-natural-number-aqr/
Based on https://github.com/tiger40490/repo1/blob/cpp1/cpp1/combo_permu/factorize_AQR.cpp

--for 36 we want
fac 36 () iterating from 2 to 6
  fac 18 (+2) iterating from 2 to 4
    fac 9 (2, +2)
      fac 3 (2,2, +3)
    fac 6 (2, +3)
  fac 12 (+3) iterating from 3 to 3
    fac 4 (3, +3)
  fac 9 (+4)    
  fac 6 (+6)
--for 12 we want
factorize 12 ()
 factorize 6 (+2)
  factorize 3 (2,+2)
 factorize 4 (+3)
'''