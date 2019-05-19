'''
showcase object id printing
showcase stride slicing
showcase defining 2 vars to one value, on the same line
showcase defining 2 unrealted vars on the same line;; separated by semicolon
'''
import random
class Stripe(object):
  def __init__(self, q):
    self.min=q
    self.max=q
  def __str__(self):
    return 'Stripe['+str(self.min) + ' ' + str(self.max) + ']\t@ ' + str(id(self)%1000)

def verifyBySorting(uniq):
  cnt=max=1
  ascd = sorted(uniq)
  for i in xrange(1, len(ascd)):
    if ascd[i-1] + 1 == ascd[i]:
      cnt += 1
    else: # a run just ended
      if (cnt > max): max = cnt
      cnt = 1
  if (cnt > max): max = cnt
  print 'verifying (by sort) ... found', max 
  return max
def solve2Wrapper(randomList):
  li = list(set(randomList))
  for _ in xrange(2):
    li = li[1::2]+li[::2]
  act = solve2(li)
  exp = verifyBySorting(li) 
  assert exp == act, 'expecting ' + str(exp)
def solve2(uniq):
  isVerbose=16 > len(uniq)
  print 'uniq =', uniq
  max=0; seen=dict() # item -> stripe. Every item must be the min or max of a stripe
  for q in uniq:
    if isVerbose: print 'procssing --> ', q
    assert q not in seen, 'original values should be unique'
    stripeLe=stripeRi=None
    stripeLen=0
    if q-1 in seen:
      stripeLe=seen[q-1]
      assert stripeLe.max+1==q
      stripeLe.max=q
      seen[q]=stripeLe
      stripeLen = stripeLe.max+1-stripeLe.min
      if isVerbose: print stripeLe, 'expanded to right'
    if q+1 in seen:
      stripeRi=seen[q+1]
      assert stripeRi.min-1==q
      stripeRi.min=q
      seen[q]=stripeRi
      stripeLen = stripeRi.max+1-stripeRi.min
      if isVerbose: print stripeRi, 'expanded to left'
    if stripeLe and stripeRi: #they both contain "q"
      del seen[q] # to reduce dict size...sometimes broken
      stripeLe.max=stripeRi.max
      seen[stripeRi.max]=stripeLe
      stripeLen=stripeRi.max+1-stripeLe.min
      print stripeLe, 'merged stripeLen =', stripeLen
    if max < stripeLen: 
        max=stripeLen
        #if isVerbose: dump(seen)
    if q not in seen:
      seen[q]=Stripe(q)
  print 'returning', max
  return max
def dump(seen):
  for key, hit in seen.iteritems():    
    print key, ':', hit
def main():
  assert 15==solve2([4, 10, 13,5, 8,12, 1,9,11,6,15,3, 7,14,2])
  #return
  solve2Wrapper(random.sample(xrange(-99, 100), 150)) # 150 2-digit ints
  solve2Wrapper([100, 4, 200, 1, 3, 2])
  solve2Wrapper([7, 4, 5, 1, 3, 2])
  solve2Wrapper([8, 4, 6, 1, 3, 2])
  solve2Wrapper([9, 4, 7, 1, 5, 8, 3, 6, 2])
main()
'''Req: https://wp.me/p74oew-5Z0
'''
