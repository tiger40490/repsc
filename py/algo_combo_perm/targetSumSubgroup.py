'''
'''
#from pprint import pprint
#from json import dumps
#from collections import defaultdict
import sys
SUCCESS='... SUCCESS :)'
def genSubGroupSums(original, tgt= -sys.maxint):
  '''Supose we have scanned 3 elements in the original, and we have a collection of N abbreviations. 
  For the next element 'j', we append 'j' to each existing abbr to generate N new abbreviations. 
  Join the lists into a list of 2N elements.
  '''  
  print ' v -  genSubGroupSums for', original, ' - v'
  subsums={0:()} # start with a single empty string
  for elem in original: 
      tmp = dict()
      for subsum, abbr in subsums.items():
        newSum = subsum+elem
        if newSum == tgt:
          print abbr+(elem,) , 'add up to target sum of', tgt, SUCCESS
          return None #special value
        tmp[newSum] = abbr + (elem,)
      subsums.update(tmp)
      #print str(len(subsums))+'-element subgroup Sums:', subsums.keys()
  assert len(subsums) <= 2**len(original)
  for k,v in subsums.items(): 
    print k, 'is a subgroup sum. One of the subgroup(s) is', v
  return subsums

def splitSimple(nums):
  ''' This split is good enough (possibly optimial) if original elements are signed. '''
  sz=len(nums)
  return nums[:sz/2],  nums[sz/2:]
  
def splitSorted(nums):
  ''' This split is slightly more efficient if all the original elements are positive
  '''
  nums.sort()
  sz=len(nums)
  return nums[::2],  nums[1::2]
  
def solve(nums, tgt):
  print ' v v v ====== solve for ===>',tgt,' ====== v v v'
  lowerHouse,higherHouse=splitSorted(nums)
  
  database1 = genSubGroupSums(lowerHouse, tgt)
  if database1 is None: return True
  database2 = genSubGroupSums(higherHouse,tgt)
  if database2 is None: return True
  for subsum1, subGroup1 in database2.iteritems():
    subsum2 = tgt - subsum1
    if subsum2 in database1:
      subGroup2 = database1[subsum2]
      print subsum1, subGroup1 
      print subsum2, subGroup2, SUCCESS
      return True
  return False

def test(nums, tgt, expected):
  assert expected == solve(nums, tgt)
def main():
  test([1, 2, 6, 9, 12, 21], 9, True)
  test([1, 2, 6, 9, 12, 21], 11, True)
  test([1, 2, 6, 9, 12, 21], 25, False)
  test([1, 2, 6, 9, 12, 21], 21, True)
if __name__ == '__main__': main()
'''Req: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41382&action=edit
'''
