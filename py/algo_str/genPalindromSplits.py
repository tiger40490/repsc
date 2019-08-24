'''
Top-down is unable to use memoization due to yield. I assume the bottom-up DP is more efficient but less intuitive

showcase: lambda + defaultdict
showcase: yield
'''
from collections import defaultdict
def isPal(t):
  for i in xrange(len(t)/2+1):
    j = len(t) - i -1
    if i >= j: return True
    if t[i] != t[j]:  return False

def compare(s):
  buOutput = botup(s)
  buUniq=verifyResult(buOutput, s)
  tdOutput = list(gen(s))
  tdUniq=verifyResult(tdOutput, s)
  if (len(tdUniq) < 9):
    print 'buttom-up allSplits:', buOutput
    print 'top-down allSplits:', tdOutput
  assert buUniq == tdUniq
  
def verifyResult(allSplits, s): 
  for Split in allSplits:
    assert ''.join(Split) == s, 'each Split must be the original string'
    for pal in Split: assert isPal(pal)
  
  for k in sorted(count.keys(), key=(lambda x: count[x]), reverse=True):
    print count[k], 'revisits:',  k #top-down
  unique = set(allSplits); cnt=len(allSplits)
  print cnt, 'splits found'
  assert len(unique) == cnt, 'duplicate Split found'
  return unique

count=defaultdict(int)
def gen(s):  #top-down recursive DP
  # due to yield, this is tough for memoization
  if len(s) == 0: yield (); return
  if len(s) == 1: yield (s,); return
  count[s] +=1
  for i in reversed(xrange(len(s))):
    tail = s[i:]
    if not isPal(tail): continue
    for newTuple in gen(s[:i]):
      yield newTuple + (tail,)

def botup(s): #bottom-up DP
  di=defaultdict(lambda:[]) # head substring -> list of splits
  di['']=[()]
  for i in xrange(1,1+len(s)):
    bigHead = s[:i]
    #print 'spliting bigHead =', bigHead
    for j in xrange(i):
      midSection = s[j:i]
      #print 'checking', midSection
      if not isPal(midSection): continue
      #print midSection, 'is palindrome:)'
      smallHead = s[:j]
      for tup in di[smallHead]:
        newsplit = tup + (midSection,)
        di[bigHead].append(newsplit)
    #print bigHead, 'can be split:', di[bigHead]
  return di[s]
    
compare('abab')
compare('ababbaabaabab')
'''Req:https://bintanvictor.wordpress.com/wp-admin/post.php?post=32291&action=edit
generate all pal partitions
'''