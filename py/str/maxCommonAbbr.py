'''
showcase lambda
showcase global declaration and assignment on one line
'''
from abbrIterative import genLongestFirst 

def checkPair(abb, hay): #abb is driver
  if len(abb) * len(hay) == 0: return False
  i=0
  sz=len(hay)
  for ch in abb:
    if i == sz: return False # past the end of haystack
    while ch != hay[i]:
      if i == sz-1: 
        return False
      i+=1
    assert ch == hay[i]    
    i+=1
  print abb, 'is an abbreviation'
  return True

def solve(word1, word2): # find distance betwewn word1 and word2
  if len(word1) > len(word2):
    long,s=word1,word2
  else:
    long,s=word2,word1  
  
  genLongestFirst(s,   lambda p:checkPair(p,long)  )
def main():
  solve('intention', 'execution')
main()
'''This solution couldn't find the edit distance but could find the longest common abbreviation between 2 words.
'''