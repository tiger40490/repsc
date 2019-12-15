'''
showcase: convert from integer ordinal to ASCII character
showcase: python set
showcase: dump string with indices underneath

My sliding window idea was simple but it took me a hour+ to implement it.

idea: 2-pointer moving in?
'''
def solve(ss, k, charValue): # sliding expanding window in O(N)
  badChars = set()
  assert len(charValue) == 26
  for i in xrange(26):
    if charValue[i] == '0':
      badChars.add(chr(ord('a') + i))
  #print badChars
  
  le=0
  ret = k # k is a conservative return value 
  cnt=0 # invariance: cnt <= k
  
  for char in ss[:k]:
    if char in badChars: cnt+=1     
  print 'initial window of size k has', cnt, 'bad characters'
  
  #le, ri and cnt all initialized. Now start sliding our expanding window
  for ri in xrange(k-1, len(ss)-1):
    print ' '.join(list(ss[le:ri+1]))
    print ' '.join(str(i%10) for i in xrange(le, ri+1)), '<-- after validating, new le=',le, '; new ri=',ri, '; cnt =', cnt, ('<-BAD' if cnt > k else '')

    if cnt > k: # slide the window, hope to reduce cnt, but cnt could keep growing as we slide
      if ss[le  ] in badChars: cnt -= 1
      le += 1
      if ss[ri+1] in badChars: cnt += 1
      print 'after sliding, cnt ==', cnt
      continue
     
    assert cnt <= k #expand by moving ri
    print 'fwd-checking', ss[ri+1]
    if ss[ri+1] in badChars: 
      cnt += 1 #increment
      #print 'new cnt =', cnt, 'may need to slide'
    if cnt<= k:
      # we could reach here with or without the 'increment' operation !
      wsize=ri+2-le
      print 'new wsize =', wsize
      assert wsize > ret, 'our window never shinks'
      ret = wsize
    
  print '========== returning', ret, cnt
  return ret , cnt
    
def test():
  assert (5,6)== solve( 'bxdefgxyzxyz',  2, '10101111111111111111111000')
  #return
  assert (6,3)== solve('abcdeabcde', 2, '10101111111111111111111111')
  assert (6,2)== solve('abbcdefg', 2, '10101111111111111111111111')
  assert (5,2)== solve('abcde', 2, '10101111111111111111111111')
  assert (14,2)== solve('abcdeb----------', 2, '10101111111111111111111111')
test()
'''Req: Given a readonly string input and a dictionary or set of bad characters, find the longest substring containing at most k bad characters.
'''