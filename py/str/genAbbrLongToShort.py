
''' Efficiency -- relies on hash table. I try to minimize memory allocation
'''
def genlevel(original):
  oldBatch = set([original])
  newBatch = set()
  cnt=0
  while len(next(iter(oldBatch))) > 1:
    for abbr in oldBatch:
      chars=list(abbr)
      for i in range(len(chars)):
        newAbbr = tuple(chars[:i] + chars[i+1:])
        if newAbbr not in newBatch:
          newBatch.add(newAbbr)
    print len(newBatch), [''.join(tu) for tu in newBatch]
    cnt += len(newBatch)
    oldBatch=newBatch
    newBatch=set()
  assert cnt+2 == 2**len(original)
  
def main():
 genlevel('abcde')
 
main()
'''Req: https://wp.me/p74oew-5V3
generate all abbr from longest.. without recursion
'''