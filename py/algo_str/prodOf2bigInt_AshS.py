'''
todo: more tests
'''
def multiply2unlimitedInts(strA, strB): # returns str (not list) for easy testing 
  assert len(strA) <= len(strB), 'left string would drive the outer loop'
  liA=[int(digit) for digit in reversed(strA)]
  liB=[int(digit) for digit in reversed(strB)]
  revProduct=[0] * (1+len(strA + strB)) # some list element can exceed 1000
  print liB
  for idxA in xrange(len(liA)): # 0 to last index
    digitA=liA[idxA]
    #print digitA
    for idxB in xrange(len(liB)):
      digitB=liB[idxB]
      revProduct[idxA+idxB] += digitA * digitB
  print revProduct, ': Each element to become single-digit ...'
  
  for i in xrange(len(revProduct)-1):
    tmpCopy=revProduct[i]
    revProduct[i]    = tmpCopy%10
    revProduct[i+1] += tmpCopy/10
  print revProduct, ': Each element should be single-digit'
  
  ret = ''.join(str(digit) for digit in reversed(revProduct))
  print ret
  assert int(ret) == int(strA) * int(strB)
  return ret
def test():
  multiply2unlimitedInts('9999999999999', '9999999999999999')
  multiply2unlimitedInts('89', '798')
  #return
  multiply2unlimitedInts('24', '18')
  multiply2unlimitedInts('84', '98446744073709551613')
test()

'''Req: given two valid but superlong strings represent unsigned ints, mutiply them using only 32-bit int multiplication

'''