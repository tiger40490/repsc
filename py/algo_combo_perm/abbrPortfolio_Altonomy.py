'''
showcase yield, which I used during the speed coding, but not necessary if we maintain a proper collection.
showcase namedtuple as a simple VO. long whitespace as delimiter between fieldnames
showcase deepcopy

Interviewer hinted that recursive solution might be easier, but I always believe the iterative solution is usually superior
* debugging
* state tracking is easier
* often more natural

'''
from pprint import pprint
from copy import deepcopy
from collections import namedtuple

# this one-liner replaces about 10 lines of class definition. Note totalCost and IDs are the field names.
Ptf = namedtuple('Ptf', 'totalCost   IDs') #IDs = a vector of indices into original table of stock prices

def iterative(table, budget):
  emptyList = [] # empty list of stock IDs
  mutableNumberInTuple = [0] # clever use of a vector of one !
  # above are the two fields of an initial Ptf.
  emptyPtfAsASubset = Ptf(mutableNumberInTuple, emptyList)
  subsets = [ emptyPtfAsASubset ] # only one subset initially.
  for i, val in enumerate(table): #val is used for totalCosts, not for generating subsets
    for j in xrange(len(subsets)):
      p = deepcopy(subsets[j]) #shallow copy only duplicates references to each vector
      p.IDs.append(i)
      p.totalCost[0] += val
      if p.totalCost[0] > budget: 
        #print p.IDs, ' --> :('
        continue
      yield p
      subsets.append(p)
    #pprint(subsets)
  print 'at end of table iteration, number of portfolios =', len(subsets)  
  # return subsets[1:] # Alternative to yield
def recur():
  ''' each time we bring out one stock from the table, we will see if we can add it to the existing portfolios. The portfolio count could double.
  '''
  pass
def genAllPtf(table, budget):
  return iterative(table, budget)  
def test1table(table, expCntOfSubsets, budget=99):
  cnt = 0 
  for p in genAllPtf(table, budget): 
    print 'a subset -----> ', p
    cnt += 1
  assert cnt == expCntOfSubsets

def main():
  test1table([77,11,22,33], expCntOfSubsets=10)
  test1table([10,11,22,33], expCntOfSubsets=15)
if __name__ == '__main__': main()
''' Req: generate all subsets of a table of stock prices, subject to a budget for the subset
Each table entry's subscript is the stock's ID. Therefore, sorting the table is questionable.
'''