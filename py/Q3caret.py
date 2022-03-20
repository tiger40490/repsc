'''
todo mark original test cases
todo: add more tests
todo: reorg code
if Z is beyond lineAbove, then that line is printed.
if Z cust into part of lineAbove, then ... look at the eg
if Z cuts into lineCtr on the left, then there will be no lineAbove
if Z is 0, then special handling?
'''

def lineB(S,Y,Z, vec):
# what if markerB is -999999?
  if markerB < 0: return # nothing to print for lineBelow
  #print 'in lineB()', markerB, Y+Z
  ret = S[markerC+1 : 1+min(markerB, Y+Z)]
  print ret[:-1] + '<-- lineB'
  vec.append(ret)

def lineC(S,Y,Z, vec):
  if markerC > 0:
    distB = abs(Y-markerB) #not needed in this lineC()
    distA = abs(Y-markerA) 
    distC = abs(Y-markerC)
    #print 'distA,distC ..', distA,distC
    if Z >= distA and Z >= distC: # 
      vec.append( S[markerA+1: markerC+1] ) #, 'case 11'
      vec.append(  (' ' * (distA-1)) + '^\n' )
    if Z >= distA and Z < distC:
      vec.append(  S[markerA+1 : Z+Y+1] )#, 'case 22'
      vec.append(  (' ' * (distA-1)) + '^\n' )
    if Z < distA and Z < distC:
      vec.append(  S[Y-Z: Y+Z+1]+'\n' )#, 'case 33'
      vec.append(  (' ' *Z) + '^\n' )
    if Z < distA and Z >= distC:
      vec.append(  S[Y-Z: markerC+1] )#, 'case 44'
      vec.append(  (' ' *min(Y,Z)) + '^\n' )
      
    print vec[-2]+vec[-1]
def lineA(S,Y,Z, vec):
  # print lineAbove 
  # what if markerA is -999?
  if markerA < 0: return #nothing to print for lineAbove
  ret = S[max(markerP, Y-Z) : markerA+1]
  print ret[:-1] + '<-- lineA'
  vec.append(ret)

def originalTestCases():
  ret = solution('// comment\nint main() {\n    return 0\n}\n', 36, 126)
  assert ret == ['\nint main() {\n', ' '*4+'return 0\n', ' '*12+'^\n', '}\n']
  ret = solution('abcde\nfghij\nklmno\n', 8, 5)
  assert ret == ['de\n', 'fghij\n', ' '*2+'^\n', 'kl']
  quit()

  # Z==0
  ret = solution('123',1,0)
  assert ret == ['2\n', '^\n']

def testAll():
  originalTestCases()
  #ret = solution('abcde\nfghij1234\nklmno\n', 8, 3)
  ret = solution('0abc',2, 33)

def solution(S,Y,Z):
  vec = list()
  find3markers(S,Y)
  lineA(S,Y,Z, vec)
  lineC(S,Y,Z, vec)
  lineB(S,Y,Z, vec)
  print vec
  return vec

def find3markers(S,Y):
  global markerP, markerC, markerA, markerB
  markerP = markerA = markerC = markerB = -999999
  # locate the 3 nlMarkers and find the distance to Y
  if S[-1] != '\n': S=S+'\n'
  newlines = list()
  for pos,char in enumerate(S):
    if char == '\n': 
      sz = len(newlines)
      if pos >= Y: # 
        markerC = pos # markerC is the position of the newline on the central line
        if sz >= 2: markerP = newlines[-2]
        if sz >= 1: markerA = newlines[-1] 
        tmp = S.find('\n', pos+1)
        if (tmp != -1): markerB = tmp
        print 'returning with markerP, markerA, markerC, markerB .. ', markerP, markerA, markerC, markerB
        return 3
      newlines.append(pos)
  print 'no newline at all!'
  return 0

testAll()
''' req: https://btv-gz.dreamhosters.com/3005/careterrorwithcontext-sachin-hrt/
'''
