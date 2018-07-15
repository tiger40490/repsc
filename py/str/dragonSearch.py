from pprint import pprint
WORD_RECORD_OFFSET=400
words =sorted(['fooo', 'barr', 'wing', 'ding', 'wing'])
wordCnt=len(words) # repeating
S = 'lingmindraboofooowingdingbarrwingmonkeypoundcake'
W = len(words[0])
hm=dict()
sz = len(S)-W+1
arr=range(sz)

class WordRecord(object):
  def __init__(self, id):
    self.wid = id+WORD_RECORD_OFFSET
    self.frq = 1
  def __repr__(self): # supports pprint
    return str(self.wid) +'/' + str(self.frq)
def solutionA():
  for i in xrange(len(words)):
    if words[i] not in hm:
      hm[ words[i] ] = WordRecord(i)
    else:
      hm[ words[i] ].frq +=1
    assert len( words[i] ) == W
  pprint(hm)
  
  # generator expression!
  requiredFrq=dict( [rec.wid, rec.frq] for _,rec in hm.items() )  
  pprint(requiredFrq)

  for pos in xrange(sz):
    substr = S[pos:pos+W]
    #print pos, substr
    rec = hm.get(substr, None) # 2-digits
    if rec:
      arr[pos] = rec.wid;
      assert substr == words[rec.wid-WORD_RECORD_OFFSET]
    else:
      arr[pos] = None
  pprint(arr) 

  ret=list()
  for dragonHead in xrange(sz):
    unused=dict(requiredFrq)
    #print '---dragon search at', dragonHead # only need arr and used
    for i in xrange(dragonHead,sz,W):
      wid = arr[i]
      if not wid: break
      if wid not in unused: break;
      unused[wid]-=1
      if unused[wid] == 0:
        del unused[wid]
      print arr[i], words[wid-WORD_RECORD_OFFSET], ' .. found at', i
    if len(unused) == 0: 
      ret.append(dragonHead)
      print '   ! dragon found starting at', dragonHead
  return ret
      
def main():
  print solutionA()
main()
'''
'''