'''
showcase set(aString), as Ashish taught me. However for time/space efficiency, better avoid hashtable when the keys are a-z. Perfect hashing would use a 26-element array.
'''
from collections import defaultdict

def solveByHashtable(vec):
  stoneCntPerLetter=defaultdict(int) # how many unique stones contain this letter
  for stone in vec:
    for ch in set(stone):
      stoneCntPerLetter[ch] += 1
  
  sz = len(vec); ret=0
  for v in stoneCntPerLetter.values():
    if v == sz: ret += 1
  return ret
def solveByArray26(vec):
  stoneCntPerLetter=[[] for x in xrange(26)] # which stones contain this letter
  sz = len(vec)
  for i in xrange(sz):
    for ch in vec[i]:
      club = stoneCntPerLetter[ ord(ch)-ord('a') ]
      if len(club)==0 or club[-1]!=i:
        club.append(i)
  ret=0
  for v in stoneCntPerLetter:
    if len(v) == sz: ret += 1
  return ret
def solve(vec):
  return solveByArray26(vec)
def test():
  assert 2 == solve(['abc', 'abc', 'bc'])
  assert 2 == solve(['abcdde', 'baccd', 'eeabg'])
test()
'''Req:
If a letter [a-z] appears in every input string (i.e. stone), then it's a good letter. Count good letters.
'''
  