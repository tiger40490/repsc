'''
todo: more tests
fix assert on 9*9
'''
def multiply2unlimitedInts(strA, strB): # returns str (not list) for easy testing 
  assert len(strA) <= len(strB)
  liA=[int(digit) for digit in reversed(strA)]
  liB=[int(digit) for digit in reversed(strB)]
  revProduct=[0] * (1+len(strA + strB)) # each list element is up to 81
  print liB
  for idxA in xrange(len(liA)): # 0 to last index
    digitA=liA[idxA]
    #print digitA
    for idxB in xrange(len(liB)):
      digitB=liB[idxB]
      revProduct[idxA+idxB] += (digitA * digitB)
  print revProduct, ': Each element to become single-digit ...'
  
  for i in xrange(len(revProduct)):
    smallProd=revProduct[i]
    #assert smallProd <=9*9
    tmp = list(str(smallProd))
    #print tmp
    if smallProd > 9:
      revProduct[i] = tmp[1] #lower digit
      revProduct[i+1] +=int(tmp[0]) #higher digit
  print revProduct
  ret=''; isWithinLeadingZeros=True
  
  # now reverse and remove leading zeros
  for digit in reversed(revProduct):
    if isWithinLeadingZeros and digit==0: continue
    isWithinLeadingZeros=False
    ret += str(digit)
  #print ret
  assert int(ret) == int(strA) * int(strB)
  return ret
def test():
  multiply2unlimitedInts('89', '798')
  #return
  multiply2unlimitedInts('24', '18')
  multiply2unlimitedInts('4', '18446744073709551613')
test()

'''Req: given two valid but superlong strings represent unsigned ints, mutiply them using only 32-bit int multiplication

'''