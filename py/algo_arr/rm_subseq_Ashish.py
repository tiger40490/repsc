'''showcase shrinking a dict while scanning its keys

A "place" or "occurrence" or "position" is represented by an index. A place can be 4 meaning 3rd position in the input array. At each position there's a "payload" or "item".

'''
from collections import defaultdict
def solve(arr):
  places=defaultdict(list) #occurrences of each duplicate payload
  for i in xrange(len(arr)):
    places[arr[i]].append(i)
  
  for k in list(places): # iterating a cloned list of dict keys
    if len(places[k]) == 1: del places[k]
  print "after remove good keys, here are the places to find the duplicate keys", places
  
  if len(places) == 0: return list() # no removal needed, too good
  
  badKeys = sorted(list(places))
  print badKeys
  lowestBadKey = badKeys[0]
  ret = places[lowestBadKey][:-1] # keep last of the lowest bad key
  print "initialized with the lowest bad key's occurrences", ret

  for k in badKeys[1:]: # O(N) loop
    myPlaces = places[k]    
    lastAdded=ret[-1]
    if lastAdded <= myPlaces[0]: # happy path
      ret.extend(myPlaces[:-1]) # keep the last occurrence of this key
      continue
      
    # now we know first occurrence of k is too early
    if myPlaces[1] < lastAdded:
      return -1 # first two occurrences are too early..give up :(
    ret.extend(myPlaces[1:])

  final = [arr[pos] for pos in ret]
  #print final
  return final

def main():
  assert [2,100] == solve([100,2,4,6,2,100])
  assert [11,11] == solve([11,11,11,33])
  assert [11,11,33] == solve([22,11,33,11,44,11,33])  
  assert ['a', 'b'] == solve('abbac')
  assert [] == solve('axybc')
main()
'''req: given array AA of non-unique natural numbers, find the shortest subsequence (no need subarray) whose elements are non-descending, such that after removing this subsequence, remaining AA elements are unique.

O(N) solution may exist. I only have something like O(N logN)
'''