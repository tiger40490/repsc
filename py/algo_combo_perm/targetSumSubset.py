'''

'''
def genShortestFirst(original):
  '''Supose we have scanned 3 chars in the original, and we have a collection of N abbreviations. 
  For the next char 'j', we append 'j' to each existing abbr to generate N new abbreviations. 
  Join the lists into a list of 2N.
  '''  
  print ' v ---  shortestFirst starting --  v'
  growing=[''] # start with a single empty string
  for ch in original: # I would now avoid this in favor of the more common for i in range(len(original))
      tmp = list()
      for abbr in growing:
        tmp.append(abbr+ch)
      growing.extend(tmp)
      print str(len(growing))+'-element', growing
  if len(original) == len(set(original)):
    assert len(growing) == 2**len(original)
  return growing

def main():
  genShortestFirst('abcd')
  return
  genShortestFirst('aabb')
  genShortestFirst('aaab')
  genShortestFirst('abaa')
if __name__ == '__main__': main()
'''Req: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41382&action=edit
A subset is a part of the original objects, perhaps including 2 duplicate objects.
'''
