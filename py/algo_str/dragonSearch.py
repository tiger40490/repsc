'''
todo: add more tests
showcase simple VO class

Note my tests are not sufficient.

If non-fixed word length, then I propose to add a self.sz to VO class, but the arr element would be multi-valued
'''
from pprint import pprint
WORD_RECORD_OFFSET=400 #400 for easy visualization, better than overloaded small integers

class WordRecord(object):
  def __init__(self, i):
    self.wid = i + WORD_RECORD_OFFSET
    self.frq = 1
  def __repr__(self): # supports pprint
    return str(self.wid) +'/' + str(self.frq)
def solutionA(unsorted):
  Dict=dict()
  words = unsorted
  #words = sorted(unsorted) #optional
  WIDTH = len(words[0])
  N = len(words)
  sz = len(haystack)-WIDTH+1 # rename to haystackLen2scan
  arr=range(sz) # the 5th element, if populated, will show the word ID of the subtring starting at 5th position of haystack

  uniqCnt=0
  for w in words:
    assert len( w ) == WIDTH
    if w in Dict:
      Dict[w].frq += 1
    else:
      Dict[w] = WordRecord(uniqCnt) 
      uniqCnt += 1
  pprint(Dict) #Dict now contains ... aWord -> its id, and also the repetition within the original list
  assert uniqCnt == len(Dict)
  
  requiredFrq=[0] * (len(Dict)+0)
  for _,rec in Dict.items():
    requiredFrq[rec.wid-WORD_RECORD_OFFSET] = rec.frq 
  print requiredFrq # the 8th element is the required frequence of the 8th word
## end of pre-processing of words
  
  for pos in xrange(sz):
    substr = haystack[pos:pos+WIDTH]
    #print pos, substr
    rec = Dict.get(substr, 0) # 2-digits
    if rec:
      arr[pos] = rec.wid;
    else:
      arr[pos] = '' # I don't like to use None to mean empty
  pprint(arr) # you can see the pattern of a dragon

#### end of an elaborate preprocessing. Now the main loop:
  
  ret=list()
  for dragonHead in xrange(len(haystack) +1 - WIDTH * N ):
    reqFrqClone=list(requiredFrq)
    uniqMissingCnt = len(Dict)
    
    #print '---dragon search at', dragonHead # only need arr and used
    for i in xrange(dragonHead,sz,WIDTH):
      wid = arr[i]
      if wid == '': break
      # at position i in haystack, we do have a valid word, whose id is wid
      idx=wid-WORD_RECORD_OFFSET
      if reqFrqClone[idx] == 0: break # this word is extraneous :(
      reqFrqClone[idx] -= 1
      if reqFrqClone[idx] == 0: uniqMissingCnt -= 1
      #print arr[i], words[idx], ' .. found at', i
      assert uniqMissingCnt >= 0
      if uniqMissingCnt == 0: 
        ret.append(dragonHead)
        print '   ! dragon found starting at', dragonHead
        break
  print ret
  dumpWithSubscript(haystack)
  return ret
def dumpWithSubscript(haystack):
  print ' '.join(list(haystack))
  print ' '.join(str(i%10) for i in xrange(len(haystack)))
      
def main():
  global haystack
  haystack = 'lingmindraboofooowingdingbarrwingwingbarrdingfooowoo'
  assert [15,47,48,49] == solutionA(['o', 'o', 'w']) #important test !
  assert [11,12,13,45] == solutionA(['o', 'o', 'f'])
  assert [17,29,31,33] == solutionA(['wi', 'ng'])
  assert [13,29] == solutionA(['fooo', 'barr', 'wing', 'ding', 'wing'])
  haystack = 'ababbabaababbabaabbbabbabbabb'
  assert [14,16,20] == solutionA(['ab', 'ab', 'ba', 'bb'])
main() 
''' https://bintanvictor.wordpress.com/2012/12/03/locate-in-a-long-sentence-a-permutation-of-my-favorite-words/
'''