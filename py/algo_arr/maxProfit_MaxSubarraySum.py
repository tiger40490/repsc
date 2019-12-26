from maxSubSum import watermark1pass, disposableCurSubarr

def maxProf_maxSubSum(deltas):
  print '------------------------------'  
  return [ byDeltaByLevel('profit', deltas),
           byDeltaByLevel('segSum', deltas),
           watermark1pass(deltas),
           disposableCurSubarr(deltas)]
def byDeltaByLevel(mode, deltas): # use byLevel algo internally
  print deltas, 'are deltas; mode is', mode
  levels = list() # in profit mode, level starts at delta[0]
  if mode=='segSum':
    levels=[0] # in the subarray-sum mode, level starts at 0 always 
  
  currentLevel=0
  for d in deltas:
    currentLevel += d
    levels.append(currentLevel)
  print 'levels are', levels

  del deltas # not needed any more, so remove the variable name from idic/namespace
  assert len(levels)
  return byLevel(levels)
def byLevel(levels):
  return watermark(levels)
  #return scan2way(levels)
def scan2way(levels): # untested
  sz = len(levels)
  fromLe = [0] * sz
  fromRi = fromLe[:] #clone
  diff = fromLe[:]
  print levels
  
  fromLe[0] = levels[0]
  for i,v in enumerate(levels):
    if i == 0: continue
    fromLe[i] = min(fromLe[i-1], v)
  print fromLe

  fromRi[-1] = levels[-1]
  for i, v in reversed(list(enumerate(levels))):
    if i == sz-1: continue
    fromRi[i] = max(fromRi[i+1], v)
  print fromRi  
  
  for i in xrange(sz):
    diff[i] = fromRi[i] - fromLe[i]
  print diff
  return max(diff)
def watermark(levels):
  lowWaterMark=levels[0]
  maxProfit=float('-inf') # final max could be negative
  for L in levels[1:] :
    #print 'Level = ', L
    newp = L - lowWaterMark
    if newp > maxProfit:
      print maxProfit, 'previous maxProfit updating to', newp      
      maxProfit = newp
      
    if L < lowWaterMark:
      print lowWaterMark, 'previous low lowWaterMark updating to', L
      lowWaterMark=L

  ret = maxProfit, lowWaterMark; print ret; 
  return ret
################

def test():
  #scan2way([5,3,2,8,4,6,1,3,6,2])
  #return
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
