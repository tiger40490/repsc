'''Req: generate in ascending order all 3-combos of 6 distinct chars. We should get 6C3 = 20 combos

Plan: First generate 6C2=15 combos. For each combo (arranged as sorted string), 
we only append a single Higher character.

Many of the 15 combos are worthless -- See the "continue".
'''
pool = list('abcdef')
C = 3

def combo(total, pp):
  '''return a list of two items --
  1) a string of pp chars
  2) a list of higher chars'''
  if pp==0: return [('', pool)]

  ret = []
  li = combo(total, pp-1)
  for partial, higherChars in li:
    print 'in outer loop ', partial, higherChars
    for i in xrange(len(higherChars)):
      ch=higherChars.pop(0)
      if len(higherChars) == 0 and pp < C: continue 
      newpair = (partial+ch, list(higherChars))
      #print 'appending ', newpair
      ret.append(newpair)
  print 'After outerloop, returning a list of len =', len(ret), \
        ', which is often lower than the combination formula thanks to CONTINUE'
  return ret

def main():
  lastPrint = ''
  for completeStr, _ in combo(len(pool),C):
    assert lastPrint < completeStr
    print completeStr,
    lastPrint = completeStr
main()
