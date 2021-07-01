'''
'''
import sys
SUCCESS='... SUCCESS :)'
class GlobalVO: # from 88lang/overloadEqOperator.py
    def __init__(self, payload=None):
        self.payload = payload
    def __eq__(self, tgt):
        ret = (self.payload == tgt)
        return ret
    def __ne__(self, tgt):
        return not self==tgt
mode=GlobalVO()

def splitSimple(arr):
  ''' This split is good enough (possibly optimial) if original elements are signed. '''
  sz=len(arr)
  return arr[:sz/2],  arr[sz/2:]
def splitSorted(arr):
  ''' This split is slightly more efficient if all the original elements are positive. 
  In such a case genSubGroupSums() should refuse to save a subsum above target sum.
  '''
  arr.sort()
  sz=len(arr)
  return arr[::2],  arr[1::2]
def split2(arr):
  ''' group the input elements into two arrays of similar size '''
  if mode=='NN': return splitSorted(arr)
  else         : return splitSimple(arr)
########### end of minor util functions ###########
  
def genSubGroupSums(original, tgt= -sys.maxint):
  ''' This function generates all subgroups of the original collection, and computes the sum for each subgroup. 
  It returns a Set of those sums. For debugging, 
  it also saves at least one subgroup for each unique sum. For example, 
  if [3,1] and [1,1,2] and [2,1,0,1] each has group sum = 4, 
  then at least one of these groups will be associated with the sum "4". 
  We can trace back how we got to 4.
  
  The algorithm (the abbreviation algorithm): Supose we have scanned 3 elements in the original, 
  and so far we have N abbreviations in a list. 
  For the next element 'j', we append 'j' to each existing abbreviation to generate N new abbreviations. 
  Join the two lists into a list of 2N elements.
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
        elif mode=='NN' and newSum > tgt: 
          continue # newSum is too high to be useful
        tmp[newSum] = abbr + (elem,)
      subsums.update(tmp)
      #print str(len(subsums))+'-element subgroup Sums:', subsums.keys()
  assert len(subsums) <= 2**len(original)
  for k,v in subsums.items(): 
    print k, 'is a subgroup sum. One of the subgroup(s) is', v
  return subsums

def solve(arr, tgt):
  print ' v v v ====== solve for ===>',tgt,' ====== v v v'
  lowerHouse,higherHouse = split2(arr)
  
  database1 = genSubGroupSums(lowerHouse, tgt)
  if database1 is None: return True
  database2 = genSubGroupSums(higherHouse,tgt)
  if database2 is None: return True
  
  for subsum1, subGroup1 in database2.iteritems():
    subsum2 = tgt - subsum1
    if subsum2 in database1:
      subGroup2 = database1[subsum2]
      print subsum1, subGroup1, 'and', subsum2, subGroup2, SUCCESS
      return True
  return False
def test(arr, tgt, expected):
  assert expected == solve(arr, tgt)
def main():
  test([1, 2, 2, 3, 3, -5, -5], -9, True)
  test([1, 2, 6, 9, 12, 21], 9, True)
  test([1, 2, 6, 9, 12, 21], 11, True)
  test([1, 2, 6, 9, 12, 21], 25, False)
  test([1, 2, 6, 9, 12, 21], 21, True)
  mode.payload='NN' # NN Meaning all original elements are non-negative
  test([1, 2, 6, 9, 12, 21], 5, False)
if __name__ == '__main__': main()
'''Req: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41382&action=edit
'''
