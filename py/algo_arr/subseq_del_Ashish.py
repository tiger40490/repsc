'''showcase shrinking a dict while iterating its keys
'''
from collections import defaultdict
#from pprint import pprint
def solve(arr):
  places=defaultdict(list) #the myPlaces of each duplicate item
  for i in xrange(len(arr)):
    places[arr[i]].append(i)
  
  for k in list(places): # iterating a cloned list of dict keys
    if len(places[k]) == 1: del places[k]
  print "after remove good keys, here are the places to find the bad keys", places
  
  if len(places) == 0: return list() # no removal needed
  
  badKeys = sorted(list(places))
  print badKeys
  lowestBadKey = badKeys[0]
  ret = places[lowestBadKey][:-1] # keep last of the lowest bad key
  print ret

  for k in badKeys[1:]:
    myPlaces = places[k]    
    lastAdded=ret[-1]
    #print ret
    if lastAdded <= myPlaces[0]: # happy path
      ret.extend(myPlaces[:-1])
      continue
      
    # now we know first occurence of k is too early
    if myPlaces[1] < lastAdded:
      return -1 # first two occurences are too early..give up :(
    ret.extend(myPlaces[1:])

  final = [arr[pos] for pos in ret]
  #print final
  return final

def main():
  assert [11,11] == solve([11,11,11,33])
  assert [11,11,33] == solve([22,11,33,11,44,11,33])
  assert ['a', 'b'] == solve('abbac')
  
main()
'''req: given array AA of non-unique natural numbers, find the shortest subsequence (no need subarray) whose elements are non-descending, such that after removing this subsequence, remaining AA elements are unique.

O(N) solution may exist. I only have something like O(N logN)
'''