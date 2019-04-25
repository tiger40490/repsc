# showcase efficiency : avoid sum() over a long list
# todo after finding [2,4,5], should give up on [2,*,*]
def recurs(hand, tgtSum, cards, used=()): # returns hit count of entire subtree
  #print 'hand=',hand,'; tgtSum=',tgtSum,'; rem=',cards,'; used=',used
  assert tgtSum>=0 
  if hand==0:
    if 0 == tgtSum:
      print 'hit', used
      return 1
    return 0
  
  hits=0
  firstCard=used[-1]+1 if used else 1
  lastCard=min(cards[-1], tgtSum)
  for card in xrange(firstCard, lastCard+1):
    remainingCards=list(cards)
    remainingCards.remove(card)
    u2=list(used)
    u2.append(card)
    hits += recurs(hand-1, tgtSum-card, remainingCards, u2)
  return hits

def solve(hand, tgtSum, cards):
  return recurs(hand, tgtSum, range(1,cards+1))
def test():
  assert 5==solve(3,11,9)
  #return
  assert 4==solve(2,11,9)
  assert 7==solve(3,17,9)
test()
'''Req: given pocker cards numbered 1 to 9, find all hands of 3 producing target tgtSum of 11
See blog 
'''