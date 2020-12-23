'''
todo: add test cases
'''

from collections import defaultdict
class Profile:    
  def __init__(self, ss, last=None):
    assert len(ss) > 0
    if last is None:
      assert ss not in profiles
      self.len = len(ss)
      self.ft = defaultdict(int)
    else:
      self.len = len(last) + len(ss)
      self.ft = dict( profiles[last].ft )
    self.update(ss) 
  def update(self, ss):
    for c in ss:
      self.ft[c] += 1     
  def __str__(self):
    ret = ""
    ret += str(self.ft)
    return ret
profiles = dict() # str -> Profile
lastDiv=''
def quickCheck(haystack, lenD):
  ''' O[ len(D) + 26 ], assuming haystack profile already constructed. No need for O(H) scan of entire haystack :)
  return 0 for success
  '''
  global lastDiv
  div = haystack[:lenD]
  print 'div='+div
  lenH = len(haystack)
  if (lenH % lenD ) > 0: return 'length check failed'
  reps = lenH / lenD
  
  if haystack not in profiles:
    profiles[haystack] = Profile(haystack)
  ftH = profiles[haystack].ft
  
  if div not in profiles:
    suffix = haystack[ len(lastDiv) : lenD ]
    #print lastDiv, suffix, lenD
    assert len(lastDiv) + len(suffix) == lenD
    #profiles[div] = Profile(lastDiv, suffix)
    profiles[div] = Profile(haystack[:lenD])
  ftD = profiles[div].ft
  lastDiv = div
  
  if len(ftH) != len(ftD): return "unique_letters set don't match"
  for k,v in ftD.items():
    v2 = ftH[k]
    if v2 != v * reps: return k + ' : has a mismatched count in div vs haystack'
  return 0 # good

def solFT(haystack): # solution based on frq table
  global lastDiv
  lastDiv=''
  for lenD in xrange(1, len(haystack)/2+1):
    res = quickCheck(haystack, lenD)
    if res == 0: return lenD
    print res
  return -1 # unsuccessful
def SolA (): #AshS, I didn't test.
  if not isPerfectDivisor(s,t): return -1
  occrence_set = set()
  smallest_substr = ''
  for c in t:
    tmp = smallest_substr + c

    if c in occrence_set:
      if isPerfectDivisor(t, smallest_substr): return len(smallest_substr)
      
      if '{}'.format(tmp) == t[0: len(tmp)]:
        smallest_substr = tmp
      else: break
    else:
      smallest_substr = tmp
      occrence_set.add(c)
      
  if not isPerfectDivisor(t, smallest_substr): return -1
  
  return len(smallest_substr)
def main():
  assert 10 == solFT('abbabbabb abbabbabb abbabbabb ')
  assert 3  == solFT('abbabbabb')
  assert -1  == solFT('dkdkdkkdkkkdkkdkdkkdkddkdddkdkd')
main()
'''Req: given a long string named haystack, find the shortest divisor string dd such that some repetition of dd equals haystack. In other words, haystack can split into a series of the divisor string dd. Return length of dd, or -1 if unsuccessful.

Personally, I feel the length of haystack (N) can be huge, so I don't prefer a brute force like "try first k chars of haystack as a candidate".

Also, the shortest divisor itself could be very lengthy. So you may need to try a lot of shorter candidates before getting lucky
'''