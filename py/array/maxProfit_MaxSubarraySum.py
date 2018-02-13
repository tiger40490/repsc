def maxProf_maxSubSum(deltas):
  print '------------------------------'  
  return [ maxByDeltaOld('profit', deltas),
           maxByDeltaOld('segSum', deltas),
		   watermark1pass(deltas),
		   disposableCurSubarr(deltas)]
def maxByDeltaOld(mode, deltas):
  print deltas, 'are deltas; mode is', mode
  levels = list() # in profit mode, level starts at delta[0]
  if mode.startswith('s'):
    levels=[0] # in the subarray-sum mode, level starts at 0 always 
  
  currentLevel=0
  for d in deltas:
    currentLevel += d
    levels.append(currentLevel)
  print 'levels are', levels

  deltas=None # not needed any more
  assert len(levels)
  return byLevel(levels)
def byLevel(levels):  
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
def watermark1pass(deltas): # watermark -- my intuitive algo on list of deltas
  level = 0; maxSubsum = deltas[0]
  lowWaterMark = 0
  for delta in deltas:
    level += delta 
    d2w = level - lowWaterMark # distance to lowWaterMark
    print 'delta =', delta, 'level=', level, 'd2w =', d2w
    if maxSubsum < d2w: 
      print maxSubsum, ' (maxsum) updating to', d2w      
      maxSubsum = d2w
    if lowWaterMark > level:
      print lowWaterMark, ' (level) updating to', level
      lowWaterMark = level
  ret = maxSubsum, lowWaterMark; print ret; 
  return ret

def disposableCurSubarr(deltas): 
  #le is the starting index of the best sub-array so far
  le = bestLe = bestRi = 0; 
  currentSubsum = bestSum = float('-inf')
  for i in xrange(len(deltas)):
    delta = deltas[i]
    #print "i=", i, "delta=", delta
    if currentSubsum > 0: # current subarray useful :)
      currentSubsum += delta
      print 'updating currentSubsum to', currentSubsum
    else: # start afresh
      le=i
      currentSubsum=delta
      print 'afresh: setting le to i and currentSubsum to delta'
      
    if bestSum < currentSubsum:
# this block is an observer, not affecting the logic
      bestSum = currentSubsum
      bestLe=le; bestRi=i
      #print "updating bestSum=", bestSum, 'bestLe=', bestLe, 'bestRi=', bestRi
  ret = bestSum, bestLe, bestRi; print ret; return ret

def test():
  a=((-2, -3, 4, -1, -2, 1, 5, -3))
  assert (7,-5)==watermark1pass(a)
  assert(7,2,6)==disposableCurSubarr(a)
  assert [(7,-5), (7,-5), (7,-5), (7,2,6)]==maxProf_maxSubSum(a)
  assert [(7,7),  (14,0), (14,0),(14,0,6)]==maxProf_maxSubSum((10, -3, 4, -1, -2, 1, 5, -3))
  assert [(6,1),  (9,0),  (9,0),  (9,0,1)]==maxProf_maxSubSum((4,5,-6,4,1,-6,4,-1,3,-7,3,1,1,-1))
  assert [(-1,-21), (-1,-21), (-1,-21), (-1,3,3)]==maxProf_maxSubSum((-2, -3, -4, -1, -2, -1, -5, -3))

def gfg(a): # looks simpler than my watermark1pass but non-intuitive
    max_so_far = float('-inf')
    capped_level = 0
    for i in range(0, len(a)):
        capped_level = capped_level + a[i]
        print 'delta =', a[i], 'capped_level =', capped_level
        
        if (max_so_far < capped_level):
            print max_so_far, ' (maxsum) updating to', capped_level
            max_so_far = capped_level
 
        if capped_level < 0:
            print capped_level, ' (capped_level) reset to 0'
            capped_level = 0
    ret = max_so_far, capped_level; print ret
test()
''' Requirement: given a list of price deltas, print
* max continuous subarray sum 
* max possible profit (or smallest loss) from one buy one sell.
Can't buy before first delta.
* low lowWaterMark
Subarray must have 0< length <= original_length.

https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/ has a simpler algo

todo: have a one-pass maxProfit() algo that work with levels; have another one-pass maxSubsum() algo that work with deltas

'''
