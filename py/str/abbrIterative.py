def genLongestFirst(original, func=None, isStrict=False):
  ''' This longest-first algo is useful for identifying the longest abbreviation among 99 potential abbreviations, such as the edit-distance problem 

  isStrict means strictly abbreviations-only.
  
  Efficiency -- 
  * relies on hash table. 
  * I try to minimize memory allocation in the innermost loop
  '''  
  if func and not isStrict:
    func(original)
  oldBatch = set([original]) # longer abbreviations
  newBatch = set() # slightly shorter abbreviations
  cnt=0
  while len(next(iter(oldBatch))) > 1:
    for abbr in oldBatch:
      chars=list(abbr)
      for i in range(len(chars)): 
        #allocating a new abbr
        newBatch.add( ''.join(chars[:i] + chars[i+1:]) )
    if func:    
      for ab in newBatch: func(ab)
    else:
      print len(newBatch), newBatch
    cnt += len(newBatch)
    oldBatch=newBatch
    newBatch=set()
  #end of while  
  if len(original) == len(set(original)):
    assert cnt+2 == 2**len(original)
  if func and not isStrict:
    func('')

def genShortestFirst(original):
  '''Supose we have scanned 3 chars in the original, and we have a collection of N abbreviations. 
  For the next char 'j', we append 'j' to each existing abbr to generate N new abbreviations. 
  Join the lists into a list of 2N.
  '''  
  growing=set(['']) # start with a single empty string
  for ch in original: # I would now avoid this in favor of the more common for i in range(len(original))
      tmp = []
      for abbr in growing:
        tmp.append(abbr+ch)
      growing.update(tmp)
      print len(growing), growing
  if len(original) == len(set(original)):
    assert len(growing) == 2**len(original)

def dummyFunc(abbr):
  print ':', abbr
def main():
  genShortestFirst('abcde')
  genLongestFirst('abcde', dummyFunc)
if __name__ == '__main__': main()
'''Req: https://wp.me/p74oew-5V3 describes the longest-first

This python script is usable as a standalone or a module.
'''
