from bisect import *
def rollBy(ch, increment):
  old = ord(ch)-ord('a')
  new = (old + increment) % 26 + ord('a')
  return chr(new)
def solve(orig, roll):
  roll.sort(reverse=True)
  for i in range(len(roll)-1,-1,-1):
    if roll[i] == 0: roll.pop()
  roll.reverse()
  print roll
  sz = len(orig); rollCnt=len(roll)
  ret = list()
  for pos in xrange(sz):
    howManyMissMe = bisect_right(roll, pos)
    ch = orig[pos]
    print howManyMissMe,'=howManyMissMe; ch=',ch
    
    newCh = rollBy(ch, rollCnt-howManyMissMe)
    print ch, newCh
    ret.append(newCh)
  print ret
  return ''.join(ret)
def main():
  assert 'dda' == solve('abz', [1,2,3])
  assert 'bca' == solve('abz', [3])
  assert 'aaaaa' == solve('vwxyz', [1,2,3,4,5])
#  solve('abc', [0,0,1,1,2,2,2,3,3])
main()
'''Req: See Deepak email 7 Mar 2019
'''