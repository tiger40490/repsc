'''Req: generate in ascending order all 3-combos of 6 distinct chars. We should get 6C3 = 20 combos

Plan: First generate 6C2=15 combos. For each combo (arranged as sorted string), 
we only append a single Higher character. Many of the 15 combos are discarded 
-- inefficient, but simple
'''
pool = list('abcdef')

def combo(total, pp):
  '''return a list of two items --
  1) a string of pp chars
  2) a list of higher chars'''
  if pp==0: return [('', pool)]

  ret = []
  li = combo(total, pp-1)
  for partial, higherChars in li:
    #print 'in outer loop ', partial, higherChars
    for i in xrange(len(higherChars)):
      ch=higherChars.pop(0)
      newpair = (partial+ch, list(higherChars))
      #print 'appending ', newpair
      ret.append(newpair)
  print 'after outerloop, return a list of len =', len(ret)
  return ret

def main():
  lastPrint = ''
  for completeStr, _ in combo(len(pool),3):
    assert lastPrint < completeStr
    print completeStr,
    lastPrint = completeStr
main()
