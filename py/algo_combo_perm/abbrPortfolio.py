'''
showcase yield, which I used during the speed coding
showcase namedtuple as a simple VO
showcase deepcopy
'''
from pprint import pprint
from copy import deepcopy
from collections import namedtuple

Ptf = namedtuple('Ptf', ['totalCost', 'IDs']) #IDs = a vector of indices into original table of stock prices

def genAllPtf(table, budget):
  subsets = [  Ptf([0],[])  ] #the empty portfolio. The [0] is a mutable number inside an immutable tuple
  for i, val in enumerate(table):
    newSubsets = deepcopy(subsets) #shallow copy only duplicates references to each vector
    for p in newSubsets:
      p.IDs.append(i)
      p.totalCost[0] += val
      if p.totalCost[0] > budget: 
        #print p.IDs, ' --> :('
        continue
      yield p
    subsets.extend(newSubsets)
    #pprint(subsets)
  
def test1table(table, expCntOfSubsets, budget=99):
  cnt = 0 
  for p in genAllPtf(table, budget): 
    print 'a subset -----> ', p
    cnt += 1
  assert cnt == expCntOfSubsets

def main():
  test1table([77,11,22,33], expCntOfSubsets=10)
if __name__ == '__main__': main()
''' Req: generate all subsets of a table of stock prices, subject to a budget for the subset
Each table entry's subscript is the stock's ID. Therefore, sorting the table is questionable.
'''