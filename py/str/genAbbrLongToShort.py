

def genlevel(original):
  ''' Efficiency -- relies on hash table. I try to minimize memory allocation
  '''
  smallhm=set([original])
  bighm=set()
  cnt=0
  while len(next(iter(smallhm))) > 1:
    for abbr in smallhm:
      chars=list(abbr)
      for i in range(len(chars)):
        shorter = tuple(chars[:i] + chars[i+1:])
        if shorter not in bighm:
          bighm.add(shorter)
    print len(bighm), [''.join(tu) for tu in bighm]
    cnt += len(bighm)
    smallhm=bighm
    bighm=set()
  assert cnt+2 == 2**len(original)
  
def main():
 genlevel('abcdef')
 
main()
'''Req: https://wp.me/p74oew-5V3
generate all abbr from longest.. without recursion
'''