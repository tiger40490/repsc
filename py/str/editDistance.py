'''
showcase lambda
showcase global declaration and assignment on one line
'''
from abbrIterative import genLongestFirst 

long=''
def _checkPair(aa, bb):
  print aa, '^', bb

def solve(word1, word2): # find distance betwewn word1 and word2
  global long; long = word1
  genLongestFirst(word2,   lambda s:_checkPair(s,long)  )
def main():
  solve('aabbcc', 'abcd')
main()
'''
'''