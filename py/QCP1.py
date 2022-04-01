'''
group strings by length and sort the clubs by that length.
start from shortest words and determine its (immutable) chainlen

pass two consecutive clubs to a cross2group(). 
if lengh diff is exactly 1, then it picks pairs and pass each pair into a func pair(). 

This func tests the 2 words, and uses (1+strs's chainlen) as strb's chainlen if the latter is unset. 

If strb already has a chainlen, then tryUpdate.
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
def check2str(strs, strb):
  print strs, strb
  sz = len(strs)
  shift=0
  for i in xrange(sz):
    #print 'i=',i,'shift=',shift
    if strs[i]!=strb[i+shift]: 
      if shift == 1:   #already shifted index in B
        return False      
      assert shift == 0
      shift = 1
      #print 'shift set to 1'
      #if strs[i]==strb[i+shift]: continue
      #print 333333
      #return False
    
    if strs[i]==strb[i+shift]: 
      if i+1 == sz: 
        #print 'reached end'
        return True
def cross2club(keyS, keyB):
  global isOver
  assert keyS +1 == keyB
  lis, lib = clubs[keyS], clubs[keyB]
  #print lis, lib
  for strs in lis:
    for strb in lib:
      #print strs, strb
      if not check2str(strs, strb): continue
      inc = registry[strs]+1
      if strb not in registry or registry[strb] < inc:
         registry[strb] = inc
         if inc > winner[0]:
           del winner[:]
           winner.extend([inc, strb])
           print 'new winner:' , winner
           if inc == clubKeys[-1]: 
             isOver=True
             return
         continue
      assert registry[strb] >= inc
def longestChain(words):
  words=set(words)
  makeClubs(words)
  for w in clubs[ clubKeys[0] ]: registry[w] = 1
  for i in xrange(1, len(clubKeys)):
    keyS, keyB = clubKeys[i-1], clubKeys[i]
    if keyS +1 == keyB: 
      if isOver: break
      cross2club(keyS, keyB)
  print registry
  return winner[0]

assert check2str('a', 'aa')
assert check2str('a', 'ab')
assert check2str('a', 'ba')
assert not check2str('a', 'bc')

longestChain(['a', 'b', 'ba', 'bca', 'bda', 'bdca'])