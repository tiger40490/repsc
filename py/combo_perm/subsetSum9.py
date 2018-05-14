Hand=0
def recurs(hand, tgtSum, cards, used):
  if tgtSum<0: return
  #print 'hand=', hand, ' ; tgtSum=', tgtSum, '; rem=', cards, '; used=',used
  assert len(used)<=Hand
  if hand==0:
    assert len(used)==Hand
    if sum(used) == tgtSum:
      print 'good', used
    #print 'returning'
    return
  assert hand>0
  for card in cards:
    remain=list(cards)
    remain.remove(card)
    u2=list(used)
    u2.append(card)
    #print 'recursing with hand=', hand-1
    recurs(hand-1, tgtSum, remain, u2)

def solve(hand, tgtSum, cards):
  global Hand
  Hand = hand
  recurs(hand, tgtSum, range(1,cards+1), ())
def test():
  solve(3, 7, 5)
test()
'''Req: given pocker cards numbered 1 to 9, find all hands of 3 producing target tgtSum of 11
See blog 

Can use a simplification of the combo code in the same dir
'''