from pprint import pprint
words =sorted(['fooo', 'barr', 'wing', 'ding']) #, 'wing'])
wordCnt=len(words)
S = 'lingmindraboofooowingdingbarrwingmonkeypoundcake'
W = len(words[0])
hm = dict()
sz = len(S)-W+1
arr=range(sz)
def solutionA():
  for i in xrange(len(words)):
    hm[ words[i] ] = i + 10
    assert len( words[i] ) == W
  pprint(hm)
  for pos in xrange(sz):
    slice = S[pos:pos+W]
    #print pos, slice
    wid = hm.get(slice, None) # 2-digits
    arr[pos] = wid;
    if (wid): assert slice == words[wid-10]
  #pprint(arr) 
  ret=list()
  for dragonHead in xrange(sz):
    used=set()
    #print '---dragon search at', dragonHead # only need arr and used
    for i in xrange(dragonHead,sz,W):
      if not arr[i]: break
      if arr[i] in used: break;
      used.add(arr[i])
      #print arr[i], words[arr[i]-10], 'found at', i
    if len(used) == wordCnt: 
      ret.append(dragonHead)
      print '   ! dragon found starting at', dragonHead
  return ret
      
def main():
  print solutionA()
main()
'''
'''