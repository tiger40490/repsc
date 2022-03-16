'''
showcase yield, which I used during the speed coding, but not necessary if we maintain a proper collection.
showcase namedtuple as a simple VO. long whitespace as delimiter between fieldnames
showcase deepcopy

Interviewer hinted that recursive solution might be easier, but I always believe the iterative solution is usually superior
* debugging
* state tracking is easier
* often more natural

In this case, many would say iterative is easier

'''
from pprint import pprint
from copy import deepcopy
from collections import namedtuple

# this one-liner replaces about 10 lines of class definition. Note totalCost and IDs are the field names.
Ptf = namedtuple('Ptf', 'totalCost   IDs') #IDs = a vector of indices into original table of stock prices

def makeEmptyPtf():
  emptyList = [] # empty list of stock IDs
  mutableNumberInTuple = [0] # clever use of a vector of one !
  # above are the two fields of an initial Ptf.
  emptyPtfAsASubset = Ptf(mutableNumberInTuple, emptyList)
  return emptyPtfAsASubset

def iterative(table, budget): #botUp
  subsets = [ makeEmptyPtf() ] # only one subset initially.
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

###### recursive solution
subsets = list() # for recursive I always prefer global vars over locals
table = list()
budget=0
def recurWrapper(newtable, newbudget):
  global budget; budget=newbudget
  del subsets[:]
  subsets.append (makeEmptyPtf())
  del table[:]
  table.extend(newtable)
  recur(len(table)-1)
  print 'at end of recurWrapper, newest ptf:', subsets[-1]
  return subsets[1:] # Alternative to yield

def recur(id): #this recursion care about only the left portion of the table up to id
  ''' returns nothing
  '''
  if id>0: recur(id-1)

  #for each ptf in the subset, try to add the last stock into the ptf and add the ptf into new
  new = list()
  for ptf in subsets:
    bigger = deepcopy(ptf)
    bigger.totalCost[0] += table[id]
    if bigger.totalCost[0] > budget: continue
    bigger.IDs.append(id);
    new.append(bigger)
  subsets.extend(new)
  #print id, '= id, now adding this many new portfolios:', len(new)

def test1table(table, expCntOfSubsets, budget=99):
  cnt = 0 
  for p in iterative(table, budget): 
    print 'a subset -----> ', p
    cnt += 1
  assert cnt == expCntOfSubsets
  recurWrapper(table, budget)
  assert  len(subsets)-1 == expCntOfSubsets

def main():
  test1table([77,11,22,33], expCntOfSubsets=10)
  test1table([10,11,22,33], expCntOfSubsets=15)
if __name__ == '__main__': main()
''' Req: generate all subsets of a table of stock prices, subject to a budget for the subset
Each table entry's subscript is the stock's ID. Therefore, sorting the table is questionable.

https://btv-gz.dreamhosters.com/wp-admin/post.php?post=19251&action=edit
'''