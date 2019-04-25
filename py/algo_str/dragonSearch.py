'''
todo: rename "words", 
showcase generator expression
showcase simple VO class

If non-fixed word length, then I propose to add a self.sz to VO class, but the arr element would be multi-valued
'''
from pprint import pprint
s = 'lingmindraboofooowingdingbarrwingwingbarrdingfooo'
#### above is input
WORD_RECORD_OFFSET=400 # easy visualization

class WordRecord(object):
  def __init__(self, i):
    self.wid = i + WORD_RECORD_OFFSET
    self.frq = 1
  def __repr__(self): # supports pprint
    return str(self.wid) +'/' + str(self.frq)
def solutionA(_words):
  Dict=dict()
  words = sorted(_words)
  WIDTH = len(words[0])
  sz = len(s)-WIDTH+1
  arr=range(sz)

  for i in xrange(len(words)):
    if words[i] not in Dict:
      Dict[ words[i] ] = WordRecord(i)
    else:
      Dict[ words[i] ].frq +=1
    assert len( words[i] ) == WIDTH
  pprint(Dict) #Dict now contains aWord -> its id and repetition within the original list
    
  requiredFrq=[0] * len(Dict) 
  for _,rec in Dict.items():
    requiredFrq[rec.wid-WORD_RECORD_OFFSET] = rec.frq 
  print requiredFrq

  for pos in xrange(sz):
    substr = s[pos:pos+WIDTH]
    #print pos, substr
    rec = Dict.get(substr, 0) # 2-digits
    if rec:
      arr[pos] = rec.wid;
      assert substr == words[rec.wid-WORD_RECORD_OFFSET]
    else:
      arr[pos] = '' # I don't like to use None to mean empty
  pprint(arr) # you can see the pattern of a dragon

  ret=list()
  for dragonHead in xrange(len(s) +1 - WIDTH * len(words) ):
    reqFrqClone=list(requiredFrq)
    wordCnt = len(requiredFrq)
    
    #print '---dragon search at', dragonHead # only need arr and used
    for i in xrange(dragonHead,sz,WIDTH):
      wid = arr[i]
      if wid == '': break
      idx=wid-WORD_RECORD_OFFSET
      if reqFrqClone[idx] == 0: break
      reqFrqClone[idx] -= 1
      if reqFrqClone[idx] == 0: wordCnt -= 1
      #print arr[i], words[idx], ' .. found at', i
      if wordCnt == 0: 
        ret.append(dragonHead)
        print '   ! dragon found starting at', dragonHead
        break
  print ret
  return ret
      
def main():
  assert [11,12,13,45] == solutionA(['o', 'o', 'f'])
  assert [17,29,31,33] == solutionA(['wi', 'ng'])
  assert [13,29] == solutionA(['fooo', 'barr', 'wing', 'ding', 'wing'])
main() # https://bintanvictor.wordpress.com/2012/12/03/locate-in-a-long-sentence-a-permutation-of-my-favorite-words/
