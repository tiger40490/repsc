'''
showcase lambda
showcase global declaration and assignment on one line
'''
from abbrIterative import genLongestFirst 

def _checkPair(sh, long):
  print sh, '^', long

def solve(word1, word2): # find distance betwewn word1 and word2
  if len(word1) > len(word2):
    long,s=word1,word2
  else:
    long,s=word2,word1  
  
  genLongestFirst(s,   lambda p:_checkPair(p,long)  )
def main():
  solve('aac', 'abcd')
main()
'''
'''