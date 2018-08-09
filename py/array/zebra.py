'''
todo: automated tests using random list -> set
todo: simplify further, like more del
showcase defining 2 vars to one value, on the same line
showcase defining 2 unrealted vars on the same line;; separated by semicolon
'''
class Stripe(object):
  def __init__(self, q):
    self.min=q
    self.max=q
  def __str__(self):
    return 'Stripe['+str(self.min) + ' ' + str(self.max) + ']\t@ ' + str(id(self)%1000)

def solve2Wrapper(randomList):
  return solve2(set(randomList))
def solve2(uniq):
  print 'uniq =', uniq
  max=0; seen=dict() # item -> stripe. Every item must be the min or max of a stripe
  for q in uniq:
    print 'procssing --> ', q
    assert q not in seen, 'original values should be unique'
    stripeLe=stripeRi=None
    if q-1 in seen:
      stripeLe=seen[q-1]
      assert stripeLe.max+1==q
      stripeLe.max=q
      seen[q]=stripeLe
      tmp = stripeLe.max+1-stripeLe.min
      if max < tmp: max = tmp
      print stripeLe, 'expanded to right'
    if q+1 in seen:
      stripeRi=seen[q+1]
      assert stripeRi.min-1==q
      stripeRi.min=q
      seen[q]=stripeRi
      tmp = stripeRi.max+1-stripeRi.min
      if max < tmp: max = tmp      
      print stripeRi, 'expanded to left'
    if stripeLe and stripeRi: #they both contain "q"
      del seen[q] # to reduce dict size...sometimes broken
      stripeLe.max=stripeRi.max
      seen[stripeRi.max]=stripeLe
      stripeLen=stripeRi.max+1-stripeLe.min
      print stripeLe, 'merged stripeLen =', stripeLen
      if max < stripeLen: 
        max=stripeLen
        dump(seen)
    if q not in seen:
      seen[q]=Stripe(q)
      #print seen[q], 'created'
  print 'returning', max
  return max
def dump(seen):
  for key, hit in seen.iteritems():    
    print key, ':', hit
def main():
  assert 15==solve2([4, 10, 13,5, 8,12, 1,9,11,6,15,3, 7,14,2])
  assert 4 ==solve2Wrapper([100, 4, 200, 1, 3, 2])
main()
'''Req: 
'''