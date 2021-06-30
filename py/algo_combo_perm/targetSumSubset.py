'''
todo: genShortestFirst() need to return the set of sums. Let's build a hash table

'''
from collections import defaultdict
subSum=defaultdict(int)
def genShortestFirst(original):
  '''Supose we have scanned 3 elements in the original, and we have a collection of N abbreviations. 
  For the next element 'j', we append 'j' to each existing abbr to generate N new abbreviations. 
  Join the lists into a list of 2N elements.
  '''  
  print ' v ---  shortestFirst starting --  v'
  growing=[()] # start with a single empty string
  for ch in original: # I would now avoid this in favor of the more common for i in range(len(original))
      sz=len(growing)
      for abbr in growing[:sz] :
        growing.append(abbr+(ch,))
      print str(len(growing))+'-element', growing
  assert len(growing) == 2**len(original)
  return growing

def main():
  genShortestFirst([0,1,2,3])
if __name__ == '__main__': main()
'''Req: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41382&action=edit
A subset is a part of the original objects, perhaps including 2 duplicate objects.
'''
