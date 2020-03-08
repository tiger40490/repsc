'''
showcase idiom: reverse-iterate a list using the index values last, last-1, ...0

showcase: character relacement by position in a string is not allowed in python, so I populate a list of chars one by one. I think this is efficient and clean. Note str.replace() creates a copy anywah. No in-place replacement.

All hackerrank tests passed, but not sure if this solution is efficient or elegant in implementation
'''
from bisect import *
def rollBy(ch, increment): # roll a character (say 'a') by the increment (say 13) would produce 'n'
  old = ord(ch)-ord('a')
  new = (old + increment) % 26 + ord('a')
  return chr(new)
def solve(orig, roll):
  roll.sort(reverse=True)
  arrSize=len(roll)
  for i in xrange(arrSize-1, -1, -1):
    if roll[i] == 0: roll.pop() # remove zeros from back of the vector
  roll.reverse() # asending order
  print 'sorted ascending with zeros removed:', roll
  
  strSize = len(orig); rollCnt=len(roll); ret = list()
  for pos in xrange(strSize):
    howManyMissMe = bisect_right(roll, pos)
    ch = orig[pos]
    print howManyMissMe,'=howManyMissMe; ch=',ch
    
    newCh = rollBy(ch, rollCnt-howManyMissMe)
    print ch, 'rolls to', newCh
    ret.append(newCh)
  print ret
  return ''.join(ret)
def main():
  assert 'dda' == solve('abz', [1,2,3])
  assert 'bca' == solve('abz', [3])
  assert 'aaaaa' == solve('vwxyz', [1,2,3,4,5])
#  solve('abc', [0,0,1,1,2,2,2,3,3])
main()
'''Req: See Deepak email 7 Mar 2019. Fairly contrived and unnatural IMHO.
'''
