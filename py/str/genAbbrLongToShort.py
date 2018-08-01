
''' Efficiency -- relies on hash table. I try to minimize memory allocation
'''
def genlevel(original):
  old = set([original])
  new = set()
  cnt=0
  while len(next(iter(old))) > 1:
    for abbr in old:
      chars=list(abbr)
      for i in range(len(chars)):
        newAbbr = tuple(chars[:i] + chars[i+1:])
        if newAbbr not in new:
          new.add(newAbbr)
    print len(new), [''.join(tu) for tu in new]
    cnt += len(new)
    old=new
    new=set()
  assert cnt+2 == 2**len(original)
  
def main():
 genlevel('abcde')
 
main()
'''Req: https://wp.me/p74oew-5V3
generate all abbr from longest.. without recursion
'''