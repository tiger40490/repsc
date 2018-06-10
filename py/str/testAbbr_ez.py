
def isAbbr(abb, hay):
  i=0
  sz=len(hay)
  for ch in abb:
    while ch != hay[i]:
      i+=1
      if i == sz: 
        return False # past hay!
    assert ch == hay[i]
    if i == sz-1:
      return True
def main():
  assert isAbbr("monkey", "mamalonkey")
main()
'''Req: https://bintanvictor.wordpress.com/2017/12/16/bbg-eq-longest-abbreviation/
'''