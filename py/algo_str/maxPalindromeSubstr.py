'''
showcase nested function update enclosing-scope pointers
showcase a for-loop with custom control on looping variable
I think algo1() is possibly O(N)
I think algo2() is still O(NN). I think there exists O(N) solutions. I don't have to discover it. I can read it in a few years.
'''
from collections import deque
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
    print aid,' algo returned -->',ret
    assert prev is None or prev == ret
  print 'search() returning...', ret
  return ret
#### Algo 1
class Member: #queue item
  def __init__(self, leftPos, rightPos):
    self.le = leftPos
    self.ri = rightPos
  def len(self): return self.ri +1 - self.le
  def str(self): return s[self.le : self.ri+1] 
  def __str__(self):  
    return '{c@'+str((self.le+self.ri)/2.0)+' '+ str(self.le) + '-' + str(self.ri)+' ' + s[self.le: self.ri+1] +' }'
  def incr2ends(self, logging):
    if self.le <= 0: return False #unable to expand to left
    if self.ri >= len(s)-1: return False #unable to expand to right
    if s[self.le-1] != s[self.ri+1]: return False
    self.le -= 1
    self.ri += 1
    if logging: print 'incr2ends() completed for', self
    return True
def algo1(logLevel=1): #1-scan
  def dump(msg='', limit=4):
    if not logging: return
    if len(msg): print '-'+msg+'->',
    for member in q: 
      print member, 
      limit -= 1
      if limit == 0: print '..more'; return
    else: print
  def updateBest(mem):
    if mem.len() > best[0].len(): 
      best[0] = mem
      if logging: print '.. new best', best[0]
  ### end of nested functions ###
  print ' vv  algo1()  vv <- ' + s;  le=0
  q = deque(); q.append(Member(0,0)); best=[q[0]]
  for i in xrange(1, len(s)):
    logging = logLevel if i > 22 else 0
    #if logging: print '  i =', i, ; dump()
    if s[i] == s[i-1]:
      youngest=q[-1] #youngest member in queue i.e it has highest self.le
      assert youngest.ri == i-1
      youngest.ri=i
      if logging: print 'just extended youngest ->', youngest
      updateBest(youngest) 
      # why can't I do continue? Well, the q[0] member may be able to expand
    else:
      q.append(Member(i,i)) # new youngest member
    if logging: print '  i =', i, ; dump()
    oo = q[0] #alias to the oldest member
    if oo.ri==i: continue # already the longest member in the queue
    assert oo.ri == i-1
    if oo.incr2ends(logging): updateBest(oo); continue
    # oldest member (might be new best) just ended ...
    updateBest(oo)
    if logging: dump('after pop, before cleanup')
    
    while oo.ri != i: #guaranteed to end up with q[0].ri == i, since s[i] itself is a member
      q.popleft() # update next oldest member
      oo = q[0] #oldest to be updated
      #if oo.ri==i: break #optional optimization
      if logging: print '.. cleaning up queue at', oo
      for _r in xrange(i, oo.ri, -1):
        _l = oo.le+oo.ri - _r
        if _l < 0: break #invalid member, to be kicked out
        if s[_l] != s[_r]: break #invalid member, to be kicked out
      else: #normal end of for-loop
        oo.le = oo.le+oo.ri - i
        oo.ri = i
        updateBest(oo)
        if logging: print 'Queue clean-up completed at', oo
  assert q[0].ri == len(s)-1
  ret = best[0].str()
  if ret == s: return -1
  return ret
def main():
  assert -1 == search('bbbb', [2,1])
  assert -1 == search('aa', [2,1])
  assert 'aa' == search('aab', [2,1])
  assert 'aa' == search('baa', [2,1])
  assert 'qwqwwqqwwqwq' == search('qwqwwqqwwqwqwq',[2,1])
  assert 'babbaabaabbab' == search('babbabbaabaabbaba',[2,1])
  assert 'aababbaabbabaa' == search('abab aabaa babb aab abb aa bba baa aab', [2,1])
  assert 'a' == search('ab da cba dba cba', [2,1]) #O(N) in algo1
  assert -1 == search('ab da cba dba cba abcabdabcadba', [2,1])
main()
'''https://bintanvictor.wordpress.com/2018/03/04/find-longest-palindrome-substring-unsolved/ has my analysis
'''
