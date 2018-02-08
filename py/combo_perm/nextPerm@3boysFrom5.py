'''5P3 == 60 line-ups expected'''

pool = 'abcde'

def perm(A, p): #return a list of two strings -- p boys, and A-P boys
  if p==0: 
    return [('', pool)]

  ret = []
  li = perm(A, p-1)
  for incompleteStr, unused in li:
    print 'in outer loop ', incompleteStr, unused
    for i in xrange(len(unused)):
      clone = list(unused)
      ch = clone.pop(i)
      newpair = (incompleteStr+ch, clone)
      ret.append(newpair)
  print 'after outerloop, return a list of len =', len(ret)
  return ret

def main():
  lastPrint = ''
  for completeStr, unused in perm(len(pool),3):
    assert lastPrint < completeStr
    print completeStr,
    lastPrint = completeStr
main()
