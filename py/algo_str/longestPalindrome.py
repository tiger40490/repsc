'''
todo: more tests
todo: minor optimization on the core idea. each time identify a homogeneous core then call startfrom(). No need for 2 calls in one iteration.
todo: start the outer iteration from center

I think this solution is still O(NN). I think there exists O(N) solutions. I don't have to discover it. I can read it in a few years.

idea: first scan to identify all the "continuum" ... useful?
idea: represent any sequence of chars as a single int, to aid comparison
'''
winner=''
s=''
def startfrom(le,ri):
  global winner  
  cnt=min(le, len(s)-1-ri) #how many chars to check on both sides
  maxPossible=cnt*2 + (ri-le+1)
  if maxPossible <= len(winner): return #reigning winner is unbeatable
  
  for i in xrange(cnt+1):
    if s[le-i]!= s[ri+i]: i-=1; break
      
  # i is still in scope!    
  newLen=2*i+ri-le+1
  if newLen > len(winner):
        winner = s[le-i : ri+i+1]
        print 'found a longer palindrome :'+ winner, le-i, ri+i

def endOfRun(i):
  for j in xrange(i+1, len(s)-1):
    print 'j=',j
    if s[i] != s[j]: 
      assert s[i]==s[j-1]
      return j-1 # could be i itself
  assert s[i] != s[len(s)-1]
  return           len(s)-1
def search(haystack): 
  haystack = haystack.replace(' ','')
  print ' '+('  '.join(list(haystack)))
  for i in range(len(haystack)): print '%2s' % i,
  print
  global s, winner; winner=''; s=haystack
  #print endOfRun(29); return
  ## end of initial set-up
  
  i=1
  while i<len(s):
    h=i; i = endOfRun(i)
    
    print h,i, '<- from endOfRun()'
    startfrom(h,i)
    i+=1
  print 'returning', winner
  return winner
    
def main():
  assert 'b' == search('ab da c ba d ba cba')
  assert 'aababbaabbabaa' == search('ababaabaababb aab abb aa bba baa aab')
  assert '212112211212' == search('21211221121212')
  assert 'babbaabaabbab' == search('babbabbaabaabbaba')

main()
'''https://bintanvictor.wordpress.com/2018/03/04/find-longest-palindrome-substring-unsolved/ has my analysis
'''
