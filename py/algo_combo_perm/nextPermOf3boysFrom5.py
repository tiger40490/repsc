'''Requirement: print all line-ups of 5 boys, in ascending order of shortcode
5P3 == 60 line-ups expected

This solution showcases
* assigning a pair (vector of 2 items) to two variables.
* taking out an item from vector by index.
'''
pool = 'abcde'
total = len(pool)

def shift1char(src, dest, i):
      srcClone = list(src)
      ch = srcClone.pop(i)
      return dest+ch, srcClone
# recursive
def perm(pick): 
  '''return a list of two strings -- pick chars, and (total - pick) chars'''
  if pick==0: return [('', pool)]

  ret = []
  li = perm(pick-1)
  for partial, unused in li:
    print 'in outer loop ', partial, unused
    for i in xrange(len(unused)):
      newpair = shift1char(unused, partial, i)
      ret.append(newpair)
  print 'after outerloop, return a list of len =', len(ret)
  return ret

def main():
  lastPrint = ''
  for completeStr, _ in perm(3):
    assert lastPrint < completeStr
    # print completeStr,
    lastPrint = completeStr
main()
