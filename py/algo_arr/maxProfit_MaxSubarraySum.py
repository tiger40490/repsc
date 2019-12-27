'''
todo: debt to become positive
'''
from maxSubSum import watermark1pass, disposableCurSubarr

def maxProf_maxSubSum(deltas):
  print '------------------------------'  
  return [ byDeltaByLevel('profit', deltas),
           byDeltaByLevel('segSum', deltas),
           watermark1pass(deltas),
           disposableCurSubarr(deltas)]
def byDeltaByLevel(mode, deltas): # This wrapper uses byLevel algos internally
  print deltas, 'are deltas; mode is', mode
  levels = list() # in profit mode, level starts at delta[0]
  if mode=='segSum':
    levels=[0] # in the subarray-sum mode, level ought to start at 0 always 
  
  currentLevel=0
  for d in deltas:
    currentLevel += d
    levels.append(currentLevel)
  print 'levels are', levels

  del deltas # not needed any more, so remove the variable name from idic/namespace
  assert len(levels)
  return byLevel(levels)
def byLevel(levels):
  return dp(levels)
  return watermark(levels)
def dp(levels): #Qihao's idea, incomplete
  debt=pnl=float('-inf')
  for i,v in enumerate(levels):
    pnl = max(pnl, v+debt)
    debt = max(debt, -v) #
  ret = (pnl, -debt)
  print 'DP returning', ret
  return ret
def scanFrom2ends(levels): # this algo assumes inaction is permitted
  print 'levels =', levels
  sz = len(levels)
  fromLe = [0] * sz
  fromRi = fromLe[:] #clone
  diff = fromLe[:]
  
  fromRi[-1] = levels[-1]
  for i, v in reversed(list(enumerate(levels))):
    if i == sz-1: continue # last element already initialized before loop
    fromRi[i] = max(fromRi[i+1], v)
  print 'maximums From Right are', fromRi #from right end, strictly non-decreasing
  
  fromLe[0] = levels[0]
  for i,v in enumerate(levels):
    if i == 0: continue
    fromLe[i] = min(fromLe[i-1], v)
    ''' if fromLe[55] == $8.2, then we know that at time#55 the algo is able to buy $8.2 at time#55 or an earlier time!
    
    If fromRi[55] == $9.4, then we also know that at #55 the algo is able to sell $9.4 at time#55 or a later time.
    
    Therefore, diff[55] is an achievable profit
    '''
  print 'minimums From Left are', fromLe #strictly non-increasing

  for i in xrange(sz):
    diff[i] = fromRi[i] - fromLe[i]
  print 'diff ', diff
  ret = max(diff)
  print 'returning', ret
  return ret
def watermark(levels): # one-buy-then-one-sell exactly.
  lowWaterMark=levels[0]
  bestPnL=float('-inf') # final max can't be zero, could be negative
  for L in levels[1:] :
    newp = L - lowWaterMark
    print 'Level = ', L, 'newp =', newp
    if newp > bestPnL:
      print bestPnL, 'previous bestPnL updating to', newp 
      bestPnL = newp
      
    if L < lowWaterMark:
      print lowWaterMark, 'previous low lowWaterMark updating to', L
      lowWaterMark=L
  ret = bestPnL, lowWaterMark; print ret; 
  return ret
################

def test():
  assert 7 == scanFrom2ends([4, 5, 9, 2, 3, 1,8, 7])
  assert 0 == scanFrom2ends([-2, -5, -9, -10, -12, -13, -18, -21]);
  a=((-2, -3, 4, -1, -2, 1, 5, -3))
  assert (7,-5)==watermark1pass(a)
  assert(7,2,6)==disposableCurSubarr(a)
  
  assert [(7,-5), (7,-5), (7,-5), (7,2,6)]==maxProf_maxSubSum(a)
  
  assert [(7,7),  (14,0), (14,0),(14,0,6)]==maxProf_maxSubSum((10, -3, 4, -1, -2, 1, 5, -3))
  
  assert [(6,1),  (9,0),  (9,0),  (9,0,1)]==maxProf_maxSubSum((4,5,-6,4,1,-6,4,-1,3,-7,3,1,1,-1))
  
  assert [(-1,-21), (-1,-21), (-1,-21), (-1,3,3)]==maxProf_maxSubSum((-2, -3, -4, -1, -2, -1, -5, -3))

test()
''' Requirement: https://bintanvictor.wordpress.com/2017/02/14/7672/
given a list of price deltas, print
* max continuous subarray sum 
* max possible profit (or smallest loss) from one buy one sell. Can't buy before first delta.
* low lowWaterMark
Subarray must have 0< length <= original_length.
'''
