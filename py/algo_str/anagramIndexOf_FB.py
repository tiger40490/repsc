'''
showcase elegant iteration range check
'''
from collections import defaultdict
#from pprint import pprint
def slidingWindowSol(pat, hay):
  sz = len(pat)
  if sz > len(hay): return -1 #failed
  tgtFrq = defaultdict(lambda:int())
  for c in pat: tgtFrq[c] += 1
  print 'tgtFrq = ', tgtFrq
  
  windowFrq = defaultdict(int)
  deficit = sz #we need that many chars for a successful match
  for front in xrange(sz):
    c = hay[front]
    if c in tgtFrq: # and windowFrq[c] < tgtFrq[c]:
      windowFrq[hay[front]] += 1
      if windowFrq[c] <= tgtFrq[c]: deficit -= 1
  if deficit == 0: return 0 
  #print 'now initial window is populated, without successful match. deficit =', deficit, windowFrq
    
  for back in xrange(len(hay)): #range is more than needed
    front = back+sz # back:=char to remove; front:=char to add into windowFrq
    
    #print 'checking', back, front, hay[back:front+1], 'deficit =',deficit, windowFrq
    if front == len(hay): return -1 # ELEGANT 
    
    c=hay[back]
    if c == hay[front]: continue
    if c in tgtFrq: # and windowFrq[c] <= tgtFrq[c]:
      windowFrq[c] -= 1 
      assert windowFrq[c] >= 0
      if windowFrq[c] < tgtFrq[c]: deficit += 1
    
    c=hay[front]
    if c in tgtFrq: # and windowFrq[c] < tgtFrq[c]:
      windowFrq[c] += 1
      if windowFrq[c] <= tgtFrq[c]:
        deficit -= 1
        if deficit == 0: return back+1
def test(result, pat, hay):
  ret = slidingWindowSol(pat, hay)
  print ret
  assert ret == result
  
test(0, 'ab', 'bab')     
test(0, 'aa', 'aab')     
test(0, 'abab' , 'abbaabab')     
#test(1, 'ab' , 'aabbaaba')     
test(3, 'aaba' , 'abbaaba')     
'''Req: 
Similar to java indexOf(string pattern, string haystack), we want the earliest index where a permutation of pattern starts.
'''