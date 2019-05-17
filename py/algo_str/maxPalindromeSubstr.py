'''
todo: more tests

showcase a for-loop with custom control on looping variable

I think this solution is still O(NN). I think there exists O(N) solutions. I don't have to discover it. I can read it in a few years.
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
     #print (le,ri),'found a longer palindrome @', (le-i,ri+i), winner

def endOfRun(i):
  for j in xrange(i+1, len(s)):
    #print 'j=',j
    if s[i] != s[j]: 
      assert s[i]==s[j-1]
      return j-1 # could be i itself
  return   len(s)-1
def verifyWinner():
  sz=len(winner)
  for le in xrange(sz/2+1):
    ri=sz-1-le
    if le >  ri: return
    assert winner[le]==winner[ri]
def search(haystack): 
  haystack = haystack.replace(' ','')
  print ' '+('  '.join(list(haystack)))
  for i in range(len(haystack)): print '%2s' % i,
  print
  global s, winner; winner=''; s=haystack
  #print endOfRun(29); return
  ## end of initial set-up
  
  i=0
  while i<len(s):
    j = endOfRun(i)
    #print i,j, '<- from endOfRun()'
    startfrom(i,j)
    i=j+1
  #print 'returning', winner
  verifyWinner()
  if winner == s: return -1 #meaning entire string is a palindrome
  return winner
    
def main():
  assert -1 == search('bbbb')
  assert 'a' == search('ab da cba dba cba')
  assert -1 == search('ab da cba dba cba abcabdabcadba')
  assert 'aababbaabbabaa' == search('ababaabaababb aab abb aa bba baa aab')
  assert 'qwqwwqqwwqwq' == search('qwqwwqqwwqwqwq')
  assert 'babbaabaabbab' == search('babbabbaabaabbaba')

main()
'''https://bintanvictor.wordpress.com/2018/03/04/find-longest-palindrome-substring-unsolved/ has my analysis
'''
