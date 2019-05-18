'''
todo: clean up the LeRi update
todo: clean up

showcase a for-loop with custom control on looping variable
I think algo2() is still O(NN). I think there exists O(N) solutions. I don't have to discover it. I can read it in a few years.
'''
from collections import deque
winner = s =''
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
def verifyAlgo2Winner():
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
  verifyAlgo2Winner()
  if winner == s: return -1 #meaning entire string is a palindrome
  return winner
def search(haystack, algos=[2]): 
  haystack = haystack.replace(' ','')
  print ' '+('  '.join(list(haystack)))
  for i in range(len(haystack)): print '%2s' % i,
  print
  global s, winner; winner=''; s=haystack
  #print endOfRun(29); return
  algoDict={1:algo1,  2:algo2}
  ## end of initial set-up
  
  ret=None
  for aid in algos:
    prev, ret = ret, algoDict[aid]()
    if ret == s: ret = -1
    print aid,' algo returned -->',ret
    assert prev is None or prev == ret
  print 'search() returning...', ret
  return ret
#### Algo 1
def verify4Algo1(le,ri):
  #print 'verifying', s[le:ri+1]
  assert le <= ri
  while le < ri:
    assert s[le] == s[ri]
    le += 1; ri -= 1
class Member: #queue member
  def __init__(self, leftPos, rightPos):
    self.le = leftPos
    self.ri = rightPos
  def len(self): return self.ri +1 - self.le
  def __str__(self):
    return '{c@'+str((self.le+self.ri)/2.0)+' '+ str(self.le) + '-' + str(self.ri)+' ' + s[self.le: self.ri+1] +' }'
  def incr2ends(self):
    if self.le <= 0: return False #unable to expand to left
    if self.ri >= len(s)-1: return False #unable to expand to right
    if s[self.le-1] != s[self.ri+1]: return False
    self.le -= 1
    self.ri += 1
    print 'incr2ends() completed for', self
    return True
def dump(q, msg='', limit=4):
  if len(msg): print '-'+msg+'->',
  for member in q: 
    print member, 
    limit -= 1
    if limit == 0: print '..more'; return
  else: print
def algo1(logLevel=1): #1-scan, to be cleaned up
  print ' vv  algo1()  vv <- ' + s;  le=0
  q = deque(); q.append(Member(0,0)); best=q[0]
  for i in xrange(1, len(s)):
    log = logLevel if i > 3 else 0
    #if log: print '  i =', i, ; dump(q)
    if s[i] == s[i-1]:
      youngest=q[-1]
      assert youngest.ri == i-1
      youngest.ri=i
      if log: print 'just extended youngest ->', youngest
      if youngest.len() > best.len(): best = youngest
          #if log: print '.. new best', best
      # why can't I do continue?
    else:
      q.append(Member(i,i)) 
    if log: print '  i =', i, ; dump(q)
    oo = q[0] #alias to the oldest member
    if oo.ri==i: continue # already the longest member in the queue
    assert oo.ri==i-1
    if oo.incr2ends():
      if oo.len() > best.len(): best = oo
      continue
    assert oo.ri != i, 'I believe oldest pal just ended'
    if i-oo.le > best.len():
        best.le, best.ri= oo.le,i-1; # cleanup
        #bestLe,bestRi=oo.le,i-1; 
        if log: print 'new winner :)', best
    q.popleft() 
    if log: dump(q, 'after pop, before cleanup')
    while True:
      oo = q[0] #oldest to be updated
      if oo.ri==i: break #optional optimization
      if log: print '.. cleaning up queue at', oo
      for _r in xrange(i, oo.ri, -1):
        _l = oo.le+oo.ri - _r
        if _l < 0: print 'failed 000'; break
        if s[_l] != s[_r]: 
          #print 'failed match ..'; 
          break
      else: 
        oo.le, oo.ri = oo.le+oo.ri - i , i
        if log: print 'clean-up completed at', oo
        if oo.len() > best.len():
          best = oo
          #bestLe,bestRi=oo.le,i-1; 
          if log: print '..... new winner :)', best
        break
      q.popleft()
  return s[best.le : best.ri+1] 
def main():
  assert -1 == search('bbbb', [2,1])
  assert -1 == search('aa', [2,1])
  assert 'aa' == search('aab', [2,1])
  assert 'aa' == search('baa', [2,1])
  assert 'a' == search('ab da cba dba cba')
  assert -1 == search('ab da cba dba cba abcabdabcadba')
  assert 'qwqwwqqwwqwq' == search('qwqwwqqwwqwqwq')
  assert 'babbaabaabbab' == search('babbabbaabaabbaba')
  assert 'aababbaabbabaa' == search('abab aabaa babb aab abb aa bba baa aab', [2,1])
                            #search('abab aabaa babb aab abb aa bba baa aab', [2,1])
main()
'''https://bintanvictor.wordpress.com/2018/03/04/find-longest-palindrome-substring-unsolved/ has my analysis
'''
