'''
todo: add test cases
todo: analyze and improve bigO
todo: is Profile.len needed?
showcase: defaultdict.copy()
'''

from collections import defaultdict
class Profile:    
  def __init__(self, suff, last=''):
    assert len(suff) > 0
    if len(last) == 0:
      print suff + ' -> ctor (no lastDiv) '
      assert suff not in profiles
      self.len = len(suff)
      self.ft = defaultdict(int)
    else:
      print 'ctor using lastDiv = ' + last
      self.len = len(last) + len(suff)
      self.ft = profiles[last].ft.copy()
    for c in suff:
      self.ft[c] += 1     
  def __str__(self):
    ret = ""
    ret += str(self.ft)
    return ret
profiles = dict() # str -> Profile
lastDiv=''
def slowCheck(haystack, lenD):
  lenH = len(haystack)
  reps = lenH / lenD
  for i in xrange(reps):
    if haystack[:lenD] != haystack[i*lenD: i*lenD+lenD]: return False
  print ':) slowCheck() passed :)'
  return True  
    
def quickCheck(haystack, lenD):
  ''' O[ len(D) + 26 ], assuming haystack profile already constructed. No need for O(H) scan of entire haystack :)
  '''
  global lastDiv
  div = haystack[:lenD]
  print 'div = '+div
  lenH = len(haystack)
  if (lenH % lenD ) > 0: return 'length check failed'
  reps = lenH / lenD
  
  if haystack not in profiles:
    profiles[haystack] = Profile(haystack)
  frqTableH = profiles[haystack].ft
  
  if div not in profiles:
    suffix = haystack[ len(lastDiv) : lenD ]
    assert len(lastDiv) + len(suffix) == lenD
    profiles[div] = Profile(suffix, lastDiv)
    #profiles[div] = Profile(haystack[:lenD])
  frqTableD = profiles[div].ft
  lastDiv = div
  
  if frqTableH.keys() != frqTableD.keys(): return "unique_letters set don't match"
  for k,v in frqTableD.items():
    v2 = frqTableH[k]
    if v2 != v * reps: return k + ' : has a mismatched count in div vs haystack'
  return 0 # good

def solFT(haystack): # solution based on frq table
  global lastDiv;  lastDiv=''
  print '==== new haystack ==== ' + haystack
  for lenD in xrange(1, len(haystack)/2+1):
    res = quickCheck(haystack, lenD)
    if res == 0 and slowCheck(haystack, lenD): 
      return lenD
    #print res
  return -1 # unsuccessful
def SolA (s, t): #AshS, tests unknown
  if not isPerfectDivisor(s,t): return -1
  occrence_set = set()
  smallest_substr = ''
  for c in t:
    tmp = smallest_substr + c
    if c in occrence_set:
      if isPerfectDivisor(t, smallest_substr): return len(smallest_substr)
      if '{}'.format(tmp) == t[0: len(tmp)]: smallest_substr = tmp
      else: break
    else:
      smallest_substr = tmp
      occrence_set.add(c)
  if not isPerfectDivisor(t, smallest_substr): return -1
  return len(smallest_substr)
def main():
  assert 10 == solFT('abbabbabb-abbabbabb-abbabbabb-')
  assert 3  == solFT('abbabbabb')
  assert -1 == solFT('dkdkdkkdkkkdkkdkdkkdkddkdddkdkd')
main()
'''Req: given a long string named haystack, find the shortest divisor string dd such that some repetition of dd equals haystack. In other words, haystack can split into a series of the divisor string dd. Return length of dd, or -1 if unsuccessful.

https://bintanvictor.wordpress.com/wp-admin/post.php?post=39095&action=edit&classic-editor has some comments.
'''