'''
'''
#from pprint import pprint
from json import dumps
from collections import defaultdict
#subSum=dict()
def genShortestFirst(original):
  '''Supose we have scanned 3 elements in the original, and we have a collection of N abbreviations. 
  For the next element 'j', we append 'j' to each existing abbr to generate N new abbreviations. 
  Join the lists into a list of 2N elements.
  '''  
  print ' v ---  shortestFirst starting --  v'
  growing={0:()} # start with a single empty string
  for elem in original: # I would now avoid this in favor of the more common for i in range(len(original))
      tmp = dict()
      for subsum, abbr in growing.items():
        tmp[subsum+elem] = abbr + (elem,)
      growing.update(tmp)
      print str(len(growing))+'-element subsetSums:', growing.keys()
  assert len(growing) <= 2**len(original)
  for k,v in growing.items(): print k,v
  return growing

def main():
  genShortestFirst([0,1,1,2])
if __name__ == '__main__': main()
'''Req: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41382&action=edit
A subset is a part of the original objects, perhaps including 2 duplicate objects.
'''
