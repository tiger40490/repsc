'''
todo: check2str needs clean-up:
Perhaps use two pointers
'''
import os
from collections import defaultdict
winner=[0, '']
isOver=False
clubs=defaultdict(list) # global dict of {length -> list of words}
clubKeys=list()
registry=defaultdict(lambda:1) #global dict of {word -> chainlen}

def makeClubs(words):
  global clubs
  for w in words:
    clubs[len(w)].append(w)
  clubs = dict(clubs)
  clubKeys.extend (sorted (clubs.keys()))
  print clubs
def check2str(strd, strc):
  print strd, strc
  sz = len(strd)
  shift=0
  for i in xrange(sz):
    #print 'i=',i,'shift=',shift
    if strd[i]!=strc[i+shift]: 
      if shift == 1:   #already shifted index in B
        return False      
      assert shift == 0
      shift = 1
      #print 'shift set to 1'
      #if strd[i]==strc[i+shift]: continue
      #print 333333
      #return False
    
    if strd[i]==strc[i+shift]: 
      if i+1 == sz: 
        #print 'reached end'
        return True
def cross2club(keyd, keyc):
  global isOver
  assert keyd +1 == keyc
  listd, listc = clubs[keyd], clubs[keyc]
  #print listd, listc
  for strd in listd:
    for strc in listc:
      #print strd, strc
      if not check2str(strd, strc): continue
      inc = registry[strd]+1
      if strc not in registry or registry[strc] < inc:
         registry[strc] = inc
         if inc > winner[0]:
           del winner[:]
           winner.extend([inc, strc])
           print 'new winner:' , winner
           if inc == clubKeys[-1]: 
             isOver=True
             return
         continue
      assert registry[strc] >= inc
def longestChain(words):
  words=set(words)
  makeClubs(words)
  for w in clubs[ clubKeys[0] ]: registry[w] = 1
  for i in xrange(1, len(clubKeys)):
    keyd, keyc = clubKeys[i-1], clubKeys[i]
    if keyd +1 == keyc: 
      if isOver: break
      cross2club(keyd, keyc)
  print registry
  print 'returning winner =', winner[0]
  return winner[0]

assert check2str('a', 'aa')
assert check2str('a', 'ab')
assert check2str('a', 'ba')
assert not check2str('a', 'bc')

longestChain(['a', 'b', 'ba', 'bca', 'bda', 'bdca'])
'''Req: https://btv-gz.dreamhosters.com/42720/word-chain-civ-by-ash-s/
'''