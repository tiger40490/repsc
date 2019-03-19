'''
todo:  ancestors and directParents should become global variables to be initialized once only and frozen
todo: dft should not rebuild the set for a node multiple times
'''
from pprint import pprint
from collections import defaultdict
parent_child_pairs = [(11,2), (1, 3), (2, 3), (3, 6), (5, 6), (5, 7), (4, 5), (4, 8), (8, 10) ]
def dft(di, c, ac): #return all ancestors of c
  if c not in di: return set()
  for p in di[c]:
    ac.add(p) # accumulator
    dft(di, p, ac)
  return ac # only used from top-level

# graph having K nodes and P edges, q2 has O(P+K) time complexity?? up to O(K*P) space complexity??
def q2(inPairs, x, y):
  # l0=list(); l1 = list() # for Q1
  directParents = defaultdict(list) # list as a default_factory
  for p, c  in inPairs:
    directParents[c].append(p)
    directParents[p] # explicitly triggers defaultdict default_factory
  #pprint(dict(directParents)) ## done with directParents
  
  ## for each of x and y, find the list of all ancestors (myAncestors)
  ancestors=dict() #child -> myAncestors
  for ch, myParents in directParents.items():
    myAncestors = dft(directParents, ch, set())
    #print ch, myParents, myAncestors 
    ancestors[ch] = myAncestors
  pprint(ancestors)

  for i in ancestors[x]:
    if i in ancestors[y]: return True
  else: return False
  
assert not q2(parent_child_pairs, 3,8)
assert q2(parent_child_pairs, 5,8)
assert q2(parent_child_pairs, 6,8)
assert not q2(parent_child_pairs, 1,3)
assert q2(parent_child_pairs, 6,3)
'''Req: Suppose we have some input data describing a graph of relationships between parents and children over multiple generations. The data is formatted as a list of (parent, child) pairs, where each individual is assigned a unique integer identifier.

For example, in this diagram, 3 is a child of 1 and 2, and 5 is a child of 4:
  11
   \
1   2   4
 \ /   / \
  3   5   8
   \ / \   \
    6   7   10
Q2: write a bool function to determine if two named individuals have any common ancestor. 3 and 6 both descend from 1; 3 and 1 no
'''
