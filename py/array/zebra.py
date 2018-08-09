'''
showcase defining 2 vars on one line
'''
class Stripe(object):
  def __init__(self, a):
    self.min=a
    self.max=a
  def __str__(self):
    return 'Stripe['+str(self.min) + ' ' + str(self.max) + ']\t@ ' + str(id(self)%1000)       
seen=dict() # item -> stripe. Every item must be the min or max of a stripe

def solve2(unsorted):
  max=0
  for q in unsorted:
    print 'procssing --> ', q
    assert q not in seen, 'original values should be unique'
    stripeLe=stripeRi=None
    if q-1 in seen:
      stripeLe=seen[q-1]
      assert stripeLe.max+1==q
      stripeLe.max=q
      seen[q]=stripeLe
      print stripeLe, 'expanded to right'
    if q+1 in seen:
      stripeRi=seen[q+1]
      assert stripeRi.min-1==q
      stripeRi.min=q
      seen[q]=stripeRi
      print stripeRi, 'expanded to left'
    if stripeLe and stripeRi: #they both contain "q"
      del seen[q] # to reduce dict size...sometimes broken
      stripeLe.max=stripeRi.max
      seen[stripeRi.max]=stripeLe
      stripeLen=stripeRi.max+1-stripeLe.min
      print stripeLe, 'merged stripeLen =', stripeLen
      if max < stripeLen: 
        max=stripeLen
        dump()
    if q not in seen:
      seen[q]=Stripe(q)
      #print seen[q], 'created'
  return max
def dump():
  for key, hit in seen.iteritems():    
    print key, ':', hit
def main():
  assert 15==solve2([4, 10, 13,5, 8,12, 1,9,11,6,15,3, 7,14,2])
#  solve1([100, 4, 200, 1, 3, 2])
main()
'''Req: 
'''