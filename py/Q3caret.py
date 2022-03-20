'''
if Z is beyond lineAbove, then that line is printed.
if Z cust into part of lineAbove, then ... look at the eg
if Z cuts into lineCtr on the left, then there will be no lineAbove
if Z is 0, then special handling?

Will focus on the right side first. 
'''

def riSide(S,Y,Z):
  pass

def lineC(S,Y,Z):
  # print the central line
  # if markerC is bad, then just print an error msg.. too complicated
  if markerC > 0:
    distA = abs(Y-markerA) 
    distC = abs(Y-markerC) 
    distB = abs(Y-markerB) #not needed in this lineC()
    if Z > distA and Z > distC: # should it be >=?
      print S[markerA+1: markerC+1] #, 'case 11'
      print (' ' * (distA-1)) + '^\n'
    if Z > distA and Z < distC:
      print S[markerA+1:Z+Y] #, 'case 22'
      print (' ' * (distA-1)) + '^\n'
    if Z < distA and Z < distC:
      print S[Y-Z: Y+Z+1]+'\n'
      print (' ' *Z) + '^\n'
    if Z < distA and Z > distC:
      print S[Y-Z, markerC+1]
      print (' ' *Z) + '^\n'

def solution(S,Y,Z):
  find3markers(S,Y)
  # print lineAbove .. todo
  lineC(S,Y,Z)

def find3markers(S,Y):
  global markerC, markerA, markerB
  markerA = markerC = markerB = -999
  # locate the 3 nlMarkers and find the distance to Y
  if S[-1] != '\n': S=S+'\n'
  newlines = list()
  for pos,char in enumerate(S):
    if char == '\n': 
      sz = len(newlines)
      if pos >= Y: # 
        markerC = pos # markerC is the position of the newline on the central line
        markerA = newlines[-1] if sz >= 1 else -999
        tmp = S.find('\n', pos+1)
        markerB = -999 if (tmp == -1) else tmp
        print 'returning with markerA, markerC, markerB .. ', markerA, markerC, markerB
        return 3
      newlines.append(pos)
  print 'no newline at all!'
  return 0
  
def test():
  #solution('// comment\nint main() {\n    return 0\n}\n', 36, 126)
  #solution('abcde\nfghij\nklmno\n', 8, 5)
  solution('123',1,0)
  #solution('123',1,1)

test()
