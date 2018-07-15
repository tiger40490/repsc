from pprint import pprint
words =sorted(['fooo', 'barr', 'wing', 'ding', 'wing'])
S = 'lingmindraboofooowingdingbarrwingmonkeypoundcake'
W = len(words[0])
hm = dict()
arr=range(len(S))
def build():
  for i in xrange(len(words)):
    hm[ words[i] ] = i + 10
    assert len( words[i] ) == W
  pprint(hm)
  for pos in xrange(len(S)-W+1):
    slice = S[pos:pos+W]
    #print pos, slice
    wid = hm.get(slice, None) # 2-digits
    arr[pos] = wid;
    if (wid): assert slice == words[wid-10]
    
def main():
  build()
main()
'''
'''