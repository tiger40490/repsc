# efficiency showcase: avoid sum() over a long list
# todo assert on result
LastCard=0
def recurs(hand, tgtSum, cards, used):
  if tgtSum<0: return
  #print 'hand=', hand, ' ; tgtSum=', tgtSum, '; rem=', cards, '; used=',used
  if hand==0:
    if 0 == tgtSum:
      print 'hit', used
    return  
  firstCard=used[-1]+1 if used else 1
  for card in range(firstCard, LastCard+1):
    remain=list(cards)
    remain.remove(card)
    u2=list(used)
    u2.append(card)
    recurs(hand-1, tgtSum-card, remain, u2)

def solve(hand, tgtSum, cards):
  global LastCard
  LastCard=cards;
  recurs(hand, tgtSum, range(1,cards+1), ())
def test():
  solve(3, 11, 9)
test()
'''Req: given pocker cards numbered 1 to 9, find all hands of 3 producing target tgtSum of 11
See blog 

Can use a simplification of the combo code in the same dir
'''