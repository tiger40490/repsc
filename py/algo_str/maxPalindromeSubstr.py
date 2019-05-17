'''
todo: identiy all ABA clusters? Not useful

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
     print 'new winner @', (le-i,ri+i), winner

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
def algo2():  
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
def search(haystack): 
  haystack = haystack.replace(' ','')
  print ' '+('  '.join(list(haystack)))
  for i in range(len(haystack)): print '%2s' % i,
  print
  global s, winner; winner=''; s=haystack
  #print endOfRun(29); return
  ## end of initial set-up
  return algo2();
def verify(le,ri):
  assert le <= ri
  while le < ri:
    assert s[le] == s[ri]
    le += 1
    ri -= 1
    
# need to handle a run
def algo1(): #1-scan unfinished
  ret=s[0];  le=ri=1; #maxLen=1; 
  for i in xrange(1, len(s)):
    ch = s[i]
    print i, 'le=',le, 'ri=',ri    
    if le > 0 and s[le-1] == ch:
      le -= 1; ri += 1
      # check the length only when this palindrome ends
      continue
    verify(le, ri)
    pal = s[le:ri+1]
    print pal, 'is a new palindrome'
    if ri-le+1 > len(ret):
      ret = pal
      print ret, 'is a new winner, from', le, 'to', ri
      #maxLen == ri-le+1
    le=ri=i    
  return ret
def main():
  assert 'aababbaabbabaa' == search('abab aabaa babb aab abb aa bba baa aab')
  #return
  assert 'qwqwwqqwwqwq' == search('qwqwwqqwwqwqwq')
  assert 'a' == search('ab da cba dba cba')
  assert -1 == search('bbbb')
  assert -1 == search('ab da cba dba cba abcabdabcadba')
  assert 'babbaabaabbab' == search('babbabbaabaabbaba')

main()
'''https://bintanvictor.wordpress.com/2018/03/04/find-longest-palindrome-substring-unsolved/ has my analysis
'''
