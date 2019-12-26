''' a module to be imported
Q: is empty subarray permitted?
A: not allow. If the best subarray sum is negative, then it's easy to determine that empty subarray has is better if permitted.
'''
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

def disposableCurSubarr(deltas): # Based on ideas in https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm_(Algorithm_3:_Dynamic_Programming)
  #le is the starting index of the best sub-array so far
  le = bestLe = bestRi = 0; 
  # currentSubum is the sum of a subarrayEndHere. Empty array? Never
  currentSubsum = bestSum = float('-inf')
  for i in xrange(len(deltas)):
    delta = deltas[i]
    #print "i=", i, "delta=", delta
    if currentSubsum > 0: # current subarray useful :)
      currentSubsum += delta
      print 'updating currentSubsum to', currentSubsum # extending the subarrayEndingHere by a new item
    else: # start afresh
      le=i
      currentSubsum=delta # if negative, then might be discard in next iteration
      print 'afresh: setting le to i and currentSubsum to delta'
      
    if bestSum < currentSubsum:
# this block is an observer, not affecting the logic
      bestSum = currentSubsum
      bestLe=le; bestRi=i
      #print "updating bestSum=", bestSum, 'bestLe=', bestLe, 'bestRi=', bestRi
  ret = bestSum, bestLe, bestRi; print ret; return ret

def gfg(a): # looks simpler than my watermark1pass but non-intuitive
# i think this is basically same as my disposableCurSubarr()
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