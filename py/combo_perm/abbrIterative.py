'''
showcase functor passed as arg
showcase next() builtin function
showcase how to get any element from a set
showcase    oldBatch, newBatch = newBatch, set()

todo: add test cases

Q: Can we make do without a hashtable? I think it would be much longer than my 7-line solution

But why is the longest-first not relying on a hashtable?
'''
retLF = set()
def genLongestFirst(original, func=None, isStrict=False):
  ''' This longest-first algo is useful for identifying the longest abbreviation among 99 potential abbreviations 

  func -- is a processorOnEchAbbr
  isStrict -- means strictly abbreviations-only, i.e. no empty string no original string
  
  Efficiency -- 
  * relies on hash table. 
  * I try to minimize memory allocation in the innermost loop
  '''  
  print ' v ---  starting longestFirst --  v'
  retLF.clear()
  if func and not isStrict:
    func(original)
  oldBatch = set([original]) # this set will hold longer abbreviations
  newBatch = set() # this set will hold slightly shorter abbreviations
  cnt=0
  sz=len(original)
  while sz > 1:
    print '... done with abbr of Length', sz, '.. Now generating Length', sz-1
    
    ## Section 1: Below for-loop is the actul algo, very brief:)
    for oldabbr in oldBatch:
      chars=list(oldabbr)
      for i in range(len(chars)): 
        #allocating a new abbr that's one-char short of the oldabbr
        newBatch.add( ''.join(chars[:i] + chars[i+1:]) )
        
    ## Section 2: observer code:
    if func:    
      for ab in newBatch: func(ab)
    else:
      print len(newBatch), newBatch
    cnt += len(newBatch)
    
    ## Section 3: prepare for next iteration of while-loop:
    oldBatch, newBatch = newBatch, set()
    sz=len(next(iter(oldBatch)))
  #end of while-loop
  if len(original) == len(set(original)): # no duplicate char
    assert cnt+2 == 2**len(original), 'count of abbreviations incorrect'
  if func and not isStrict:
    func('')
  print 'longest-first algo found', len(retLF), 'unique abbreviations:', retLF
def dummyFunc(abbr):
  retLF.add(abbr)
  print len(retLF),':', abbr

def genShortestFirst(original):
  '''Supose we have scanned 3 chars in the original, and we have a collection of N abbreviations. 
  For the next char 'j', we append 'j' to each existing abbr to generate N new abbreviations. 
  Join the lists into a list of 2N.
  '''  
  growing=set(['']) # start with a single empty string
  for ch in original: # I would now avoid this in favor of the more common for i in range(len(original))
      tmp = list()
      for abbr in growing:
        tmp.append(abbr+ch)
      growing.update(tmp)
      print str(len(growing))+'-element', growing
  if len(original) == len(set(original)):
    assert len(growing) == 2**len(original)
  return growing

def test1(orig):
  growing = genShortestFirst(orig)
  genLongestFirst(orig, dummyFunc)
  assert( len(retLF) == len(growing))
def main():
  test1('aaab')
if __name__ == '__main__': main()
'''Req: https://wp.me/p74oew-5V3 describes the longest-first

This python script is usable as a standalone or a module.
'''
