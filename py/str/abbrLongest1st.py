# merged into abbrIterative.py


def genLongestFirst(original):
  ''' Efficiency -- relies on hash table. 
  I try to minimize memory allocation in the innermost loop
  '''
  oldBatch = set([original]) # longer abbreviations
  newBatch = set() # slightly shorter abbreviations
  cnt=0
  while len(next(iter(oldBatch))) > 1:
    for abbr in oldBatch:
      chars=list(abbr)
      for i in range(len(chars)): 
        #allocating a new abbr
        newBatch.add( ''.join(chars[:i] + chars[i+1:]) )
    print len(newBatch), newBatch # here u can process the abbreviations
    cnt += len(newBatch)
    oldBatch=newBatch
    newBatch=set()
  #end of while  
  if len(original) == len(set(original)):
    assert cnt+2 == 2**len(original)
  
def main():
 genLongestFirst('abcdef')
if __name__ == '__main__': main()
'''Req: https://wp.me/p74oew-5V3
generate all abbr from longest.. without recursion

Usable as a standalone or a module
'''