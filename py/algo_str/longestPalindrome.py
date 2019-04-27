'''
todo: minor optimization on the core idea. each time identify a homogeneous core then call startfrom(). No need for 2 calls in one iteration.
todo: start the outer iteration from center
todo: early exit from startfrom

I think this solution is still O(NN). I think there exists O(N) solutions. I don't have to discover it. I can read it in a few years.

idea: first scan to identify all the "continuum" ... useful?
idea: represent any sequence of chars as a single int, to aid comparison
'''
winner=''

def startfrom(s, le,ri):
  global winner  
  cnt=min(le, len(s)-1-ri) #how many chars to check on both sides
  maxPossible=cnt*2+ri-le+1
  if maxPossible <= len(winner): return
  
  for i in range(1,cnt+1):
    if s[le-i]!= s[ri+i]: 
      i-=1
      break
      
  # i is still in scope!    
  newLen=2*i+ri-le+1
  if newLen > len(winner):
        winner = s[le-i:ri+i+1]
        print 'found a longer palindrome :', winner

def search(haystack): 
  global winner
  winner=''
  for i in range(1, len(haystack)-1):
    startfrom(haystack, i,i)
    if haystack[i]==haystack[i+1]:
      startfrom(haystack, i,i+1)
  return winner
    
def main():
  assert '212112211212' == search('21211221121212')
  assert 'babbaabaabbab' == search('babbabbaabaabbaba')

main()
'''https://bintanvictor.wordpress.com/2018/03/04/find-longest-palindrome-substring-unsolved/ has my analysis
'''
