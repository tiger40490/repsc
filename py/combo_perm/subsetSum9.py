# showcase efficiency : avoid sum() over a long list
def recurs(hand, tgtSum, cards, used=()): # returns hit count of entire subtree
  if tgtSum<0: return 0
  #print 'hand=',hand,'; tgtSum=',tgtSum,'; rem=',cards,'; used=',used
  if hand==0:
    if 0 == tgtSum:
      print 'hit', used
      return 1
    return 0
  firstCard=used[-1]+1 if used else 1
  hits=0
  for card in range(firstCard, cards[-1]+1):
    remain=list(cards)
    remain.remove(card)
    u2=list(used)
    u2.append(card)
    hits += recurs(hand-1, tgtSum-card, remain, u2)
  return hits

def solve(hand, tgtSum, cards):
  return recurs(hand, tgtSum, range(1,cards+1))
def test():
  assert 5==solve(3,11,9)
  assert 4==solve(2,11,9)
  assert 7==solve(3,17,9)
test()
'''Req: given pocker cards numbered 1 to 9, find all hands of 3 producing target tgtSum of 11
See blog 
'''