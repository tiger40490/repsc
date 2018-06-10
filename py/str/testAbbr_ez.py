# showcase defining a function after calling it

def main():
  findLongestAbbr("internationalization", 
    ['inter','national','nation','in','int','nationaliz'])
  assert not isAbbr("int", 'iii')
  assert not isAbbr("i", 'i5')
  assert     isAbbr("internationalization", "in")
  assert     isAbbr("mamalonkey", "mamalon")
  assert     isAbbr("mamalonkey", "monkey")
def findLongestAbbr(hay, li):
  li.sort(key=len, reverse=True) # in-place !
  for abb in li:
    print 'trying', abb, hay
    if isAbbr(hay, abb): return len(abb)
  return None 
def isAbbr(hay, abb):
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
main()
'''Req: https://bintanvictor.wordpress.com/2017/12/16/bbg-eq-longest-abbreviation/
'''