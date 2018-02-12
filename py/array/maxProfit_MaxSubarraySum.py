def maxProf_maxSubSum(deltas):
  return [ maxEither('profit', deltas),
           maxEither('segSum', deltas)]
def maxEither(mode, deltas):
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
  watermark=levels[0]
  maxProfit=float('-inf') # final could be negative
  for L in levels[1:] :
    #print 'Level = ', L
    newp = L - watermark
    if newp > maxProfit:
      print maxProfit, 'previous maxProfit updating to', newp      
      maxProfit = newp
      
    if L < watermark:
      print watermark, 'previous low watermark updating to', L
      watermark=L

  ret = maxProfit, watermark
  print ret; return ret
def test():
  #assert [(-1,-21), (-1,-21)]==maxProf_maxSubSum((-2, -3, -4, -1, -2, -1, -5, -3))
  #assert [(6,1), (9,0)]==maxProf_maxSubSum((4,5,-6,4,1,-6,4,-1,3,-7,3,1,1,-1))
  #assert [(7,-5), (7,-5)]==maxProf_maxSubSum((-2, -3, 4, -1, -2, 1, 5, -3))
  assert [(7,7), (14,0)]==maxProf_maxSubSum((10, -3, 4, -1, -2, 1, 5, -3))

test()
''' Requirement: given a list of price deltas, print
* max continuous subarray sum 
* max possible profit (or smallest loss) from one buy one sell.
Can't buy before first delta.
* low watermark
Subarray must have 0< length <= original_length.
'''
