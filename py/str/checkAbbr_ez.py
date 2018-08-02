# showcase sorting words by length. A max-heap might be faster.
# showcase defining a function after calling it
def main():
  findLongestAbbr("internationalization", 
    ['inter','national','nation','in','int','nationaliz'])
  assert not isAbbr("int", 'iii')
  assert not isAbbr("i", 'i5')
  assert     isAbbr("internationalization", "in")
  assert     isAbbr("mamalonkey", "mamalon")
  assert     isAbbr("mamalonkey", "monkey")
def isAbbr(hay, abb): #hay is driver
'''Q: Why is this solution simpler?
A: no nested loop. If abb drives outer loop, we need inner loop to scan hay:(
A: we need to increment i only in one place
'''
  i=0
  sz=len(abb)
  for ch in hay:
    if ch == abb[i]:
      if i == sz-1: 
        print abb, 'is good'
        return True
      i+=1
  assert i < sz   
  return False
def isAbbr1(hay, abb): #abb is driver
  if len(abb) * len(hay) == 0: return False
  i=0
  sz=len(hay)
  for ch in abb:
    if i == sz: return False # past the end of haystack
    while ch != hay[i]:
      if i == sz-1: 
        return False
      i+=1
    assert ch == hay[i]    
    i+=1
  print abb, 'is good'
  return True
def findLongestAbbr(hay, li):
  li.sort(key=len, reverse=True) # in-place sort !
  for abb in li:
    print 'trying', abb, hay
    if isAbbr(hay, abb): return len(abb)
  return None   
main()
'''Req: https://bintanvictor.wordpress.com/2017/12/16/bbg-eq-longest-abbreviation/
'''