'''
showcase iterating unique values of a dict
showcase using regext to parse something like '12A 3B'
'''
import re
from pprint import pprint
b2=dict() #belong2 is a lookup map of cell -> ship object
class Ship: 
  def __init__(self, shStr):
    self.dead=0 #count of hit cells
    self.alive=0 #count of unhit cells
    self.shStr=shStr # for printing
    m = re.search('(\d+)([A-Z]) (\d+)([A-Z]).*', shStr)
    s=m.groups()
    for col in xrange(ord(s[1]),ord(s[-1])+1):
      for row in xrange(int(s[0]), int(s[2])+1):
        cell = str(row)+chr(col)
        b2[cell] = self
        self.alive += 1 
    print 'Ship constructed', str(self)
    pprint (b2)
  def __repr__(self): return str(self)
  def __str__(self): return '[ ' + self.shStr + str(self.alive) + '=alive]'
def parseShips(sss):
  for shStr in sss.split(','):
    print shStr
    Ship(shStr+' ')
def parseHits(ttt):
  for hit in ttt.split():
    print hit
    if hit not in b2: continue
    ship = b2[hit]
    ship.alive -= 1
    ship.dead  += 1
    print ship
def solution(N, S, T):
  b2.clear()
  sunk=partial=0
  parseShips(S)
  parseHits(T)
  print 'iterate over all unique ships'
  for ship in set(b2.values()):
    print ship
    if ship.alive==0: 
      sunk+=1; continue
    if ship.dead > 0:
      partial += 1
  return str(sunk) + ',' + str(partial)
def test(N, sss, ttt, expected):
  assert solution(N, sss, ttt) == expected  
def main():
 assert solution(4, "1B 2C,2D 4D",  "2B 2D 3D 4D 4A") == '1,1' #1 sunk 1 partial
 assert solution(3, "1A 1B,2C 2C",  "1B") == '0,1' #1 partial
 assert solution(12,"1A 2A,12A 12A","12A") == '1,0' #no hit
main()
'''Req: Given a list of ships and a list of bomb hit locations, return count of sunk ships and count of partially hit ships.
Each ship is a rectangle (up to four cells) defined by northwest corner coordinate and southeast coordinate. Ship is sunk if all its constituent cells are each hit by a bomb

Performance is not required.
'''