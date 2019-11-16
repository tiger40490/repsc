'''
For a given Morse encoded msg,
* A translation is a sequence of English letters using up entire Morse msg
* A solution is full set of translations
'''
from collections import deque
lO='---'
lP='.--.'
lT='-'
lI='..'
lV='...-'
lE='.'
lR='.-.'
decoding={ lO:'O' ,  lP:'P' ,  lT:'T' ,  lI:'I' ,
          lV:'V' ,  lE:'E' ,  lR:'R' }
MAX_SEG= max(map(len, decoding.keys()))

'''
vector of dictionaries
sol[0] is The solution for the length-0 prefix of the Morse msg. Length zero has a empty solution.
sol[full length] is The solution for entire Morse msg
Each dict is lastLetter -> an earlier element in the same vector. 
'''
sol=list()

''' Scan forward. At each pos, build the Solution (i.e. list of valid translations up-to-here.)
When we iterate to next pos, look at the 1-char suffix, 2-char suffix, 3-char suffix ...
Make use of previous solutions. 
Uniqueness is guaranteed due to the last letter in each translation.
'''
def decodeMorse(msg, expected): #return sorted list of translations, as a solution
  print ' '.join(list(msg))
  print ' '.join(map(str, range(len(msg)))) # the positions
  for i in xrange(1+len(msg)):
    print 'v v v v   i =',i
    translations=dict()
    # try last 1-char, last 2-char, last 3-char etc
    for b in xrange(min(i,MAX_SEG)):
      back = b+1 #leng of the trailing segment
      lastSeg = msg[i-back : i]
      if lastSeg not in decoding: continue
      #print 'trying', lastSeg, 'for back =', back
      #print lastSeg, 'is a', decoding[lastSeg]
      translations[decoding[lastSeg]] = i-back
    sol.append(translations) # save The solution for the corrent position
    print '^ ^ ^ ^  ', translations
  print 'char-by-char forward scan completed. Now print all paths from leaf to root, uisng BFS'
  
  class QueueItem():
    def __init__(self, indexIntoMsg, pathToRoot):
      self.idx = indexIntoMsg
      self.path = pathToRoot  
  ret=list()
  queue=deque([  QueueItem( len(sol)-1, '')  ]) # root node in tree
  while queue: 
    pop = queue.popleft()
    #print 'popleft:', pop.idx
    if pop.idx==0: ret.append(pop.path)
    translations = sol[ pop.idx ]
    for letter,idx in translations.iteritems():
      queue.append( QueueItem(idx, letter+pop.path) )
  print ret
  assert expected==len(ret)
  return sorted(ret)

decodeMorse('.-...-', 6)