'''
'''
#from pprint import pprint
from json import dumps
from collections import defaultdict
def genSubGroupSums(original):
  '''Supose we have scanned 3 elements in the original, and we have a collection of N abbreviations. 
  For the next element 'j', we append 'j' to each existing abbr to generate N new abbreviations. 
  Join the lists into a list of 2N elements.
  '''  
  print ' v ---  shortestFirst starting --  v'
  subsums={0:()} # start with a single empty string
  for elem in original: 
      tmp = dict()
      for subsum, abbr in subsums.items():
        tmp[subsum+elem] = abbr + (elem,)
      subsums.update(tmp)
      print str(len(subsums))+'-element subgroup Sums:', subsums.keys()
  assert len(subsums) <= 2**len(original)
  for k,v in subsums.items(): 
    print k, 'is a subgroup sum. One of the subgroup(s) is', v
  return subsums

def main():
  genSubGroupSums([0,1,1,2])
if __name__ == '__main__': main()
'''Req: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41382&action=edit
'''
