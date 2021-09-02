'''
showcase yield
showcase namedtuple
showcase deepcopy
'''
from pprint import pprint
from copy import deepcopy
from collections import namedtuple

Ptf = namedtuple('Ptf', ['sum', 'IDs']) #IDs = a vector of indices into original table of stock prices

def genAllPtf(table, budget):
  subsets = [Ptf([0],[]) ] #the empty portfolio
  for i, val in enumerate(table):
    newSubsets = deepcopy(subsets) #shallow copy only duplicates references to each vector
    for p in newSubsets:
      p.IDs.append(i)
      p.sum[0] += val
      if p.sum[0] > budget: continue
      yield p
    subsets.extend(newSubsets)
    #pprint(subsets)
  
def testPortfolio(table, budget=99): 
  for p in genAllPtf(table, budget): print 'a subset -----> ', p

def main():
  testPortfolio([77,11,22,33])
if __name__ == '__main__': main()
''' Req: generate all subsets of a fixed table of stock prices, subject to a budget
Each table entry's subscript is the stock's ID.
'''