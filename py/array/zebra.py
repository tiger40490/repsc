class Stripe(object):
  def __init__(self, a):
    L2=[a,a]
    self.pair=list([L2])
  def max(self, m):
    self.pair[0][1]=m
  def min(self, m):
    self.pair[0][0]=m
    
  def __str__(self):
    return 'Stripe['+str(self.pair[0][0]) + '-' + str(self.pair[0][1]) + ']\t l-' + str(id(self.pair[0])%1000) + ' <-' + str(id(self.pair)%1000) +' <-'+ str(id(self)%1000)    
seen=dict() # item -> stripe. Every item must be the min or max of a stripe

def solve2(li):
  for it in li:
    print 'procssing --> ', it
    assert it not in seen
    stripeLe=None
    if it-1 in seen:
      stripeLe=seen[it-1]
      assert stripeLe.pair[0][1]+1==it
      stripeLe.max(it)
      seen[it]=stripeLe
      print stripeLe, 'expanded'
    stripeRi=None
    if it+1 in seen:
      stripeRi=seen[it+1]
      assert stripeRi.pair[0][0]-1==it
      stripeRi.min(it)
      seen[it]=stripeRi
      print stripeRi, 'expanded'
    if stripeLe and stripeRi: #overlap!
      #del seen[it] 
      stripeLe.max(stripeRi.pair[0][1])
      stripeRi.pair[0] = stripeLe.pair[0]
      stripeRi.pair = stripeLe.pair
      stripeLen=stripeRi.pair[0][1]+1-stripeLe.pair[0][0]
      print stripeLe, 'merged stripeLen =', stripeLen
      dump()
    if it not in seen:
      seen[it]=Stripe(it)
      print seen[it], 'created'
  #dump()  
def dump():
  for key, hit in seen.iteritems():    
    print key, hit
absentee=dict()
def solve1(li):
  for item in li: #set(li):
    print 'procssing --> ', item
    if item not in absentee:
      stripe=Stripe(item)
      print stripe, 'created'
    else: # expand existing stripe
      hit = absentee[item]
      if   hit.isOverMin:
        assert hit.stripe.min-1 == item
        hit.stripe.min -= 1
        #checkJoinUsingSeen(item-1)
      else:
        assert hit.isOverMax
        assert hit.stripe.max+1 == item
        hit.stripe.max += 1
        #checkJoinUsingSeen(item+1)
      stripe=hit.stripe
      print stripe, 'expanded'
      del absentee[item]
    # now stripe identified
    
    # before inserting into absentee, we need to check if it's already there
    if item-1 in absentee:
      hit = absentee[item-1]
      assert hit.isOverMax
      print item-1, 'will join two stripes:)'
      dump()
      return      
    absentee[item-1]=Hit(stripe,True, item-1)
    
    if item+1 in absentee:
      hit = absentee[item+1]
      assert hit.isOverMin
      print item+1, ' (unseen) will join two stripes:)'
      dump()
      return      
    absentee[item+1]=Hit(stripe,False, item+1)
class Hit(object):
  def __init__(self, stripe, isMin, i):
    self.stripe=stripe
    self.isOverMin=isMin
    self.isOverMax=not isMin
    self.boundary=i
  def __str__(self):
    return str(self.stripe)+ ' '+str(self.boundary)+' is ' + ('overMax' if self.isOverMax else 'overMin')
def main():
  #solve2([4,5, 8, 1,9,6,3, 7,2])
  solve2([4, 10, 13,5, 8,12, 1,9,11,6,15,3, 7,14,2])
#  solve1([100, 4, 200, 1, 3, 2])
main()
'''Req: 
'''