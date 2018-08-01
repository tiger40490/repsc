'''Abbrv generator. I wrote a recursive c++ solution to output in ascending order. 
Today I will forgo ascending order and try an iterative soution
Supose we have scanned 3 chars in the original, and we have a collection of N abbreviations. 
For the next char 'j', we append 'j' to each existing abbr to generate N new abbreviations. 
Join the lists into a list of 2N.
'''  
def genShortestFirst(original):
  growing=set(['']) # start with a single empty string
  for ch in original: # I would now avoid this in favor of the more common for i in range(len(original))
      tmp = []
      for abbr in growing:
        tmp.append(abbr+ch)
      growing.update(tmp)
      print len(growing), growing
  if len(original) == len(set(original)):
    assert len(growing) == 2**len(original)
      
def main():
  genShortestFirst('abcde')
if __name__ == '__main__': main()
