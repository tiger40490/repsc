'''
todo: reorg code
if Z is beyond lineAbove, then that line is printed.
if Z cust into part of lineAbove, then ... look at the eg
if Z cuts into lineCtr on the left, then there will be no lineAbove
if Z is 0, then special handling?
'''

def lineA(S,Y,Z, vec):
  # print lineAbove 
  # what if markerA is -999?
  if markerA < 0: return #nothing to print for lineAbove
  ret = S[max(markerP, Y-Z) : markerA+1]
  print ret[:-1] + '<-- lineA'
  vec.append(ret)

def lineB(S,Y,Z, vec):
# what if markerB is -999999?
  if markerB < 0: return # nothing to print for lineBelow
  print 'in lineB()', markerC, Y+Z
  if Y+Z <= markerC: return # the Z chars afer Y is before or up to the newline
  ret = S[markerC+1 : 1+min(markerB, Y+Z)]
  print ret[:-1] + '<-- lineB'
  vec.append(ret)

def lineC(S,Y,Z, vec):
  if markerC > 0:
    distB = abs(Y-markerB) #not needed in this lineC()
    distA = abs(Y-markerA) 
    distC = abs(Y-markerC)
    #print 'distA,distC ..', distA,distC
    if Z >= distA and Z >= distC: 
      vec.append( S[markerA+1: markerC+1] )
      vec.append(  (' ' * (distA-1)) + '^\n' )
    if Z >= distA and Z < distC:
      print 22222222
      vec.append(  S[markerA+1 : Z+Y+1] )
      assert vec[-1][-1] != '\n'
      vec.append(  '\n'+ (' '* (distA-1)) + '^\n' )
    if Z < distA and Z < distC:
      print 3333333
      vec.append(  S[Y-Z: Y+Z+1]+'\n' )
      vec.append(  (' ' *Z) + '^\n' )
    if Z < distA and Z >= distC:
      print 4444444
      print markerC+1
      vec.append(  S[Y-Z: markerC+1] )
      tmp = (' ' *min(Y,Z)) + '^\n'
      if vec[-1][-1] != '\n': tmp = '\n'+tmp
      vec.append(tmp)
    print vec[-2]+vec[-1]

def testAll():
  originalTestCases()
  
  # Z cuts into original lineC
  ret = solution('abcde\nfghij1234\nklmno\n', 8, 3)
  assert ret == ['\n', 'fghij1', '\n  ^\n']

  # Z includes the newline of lineC
  ret = solution('abcde\nfghij\nklmno\n', 8, 3)
  assert ret == ['\n', 'fghij\n', '  ^\n']

  #large Z
  ret = solution('0abc',2, 9)
  assert ret == ['0abc', '\n  ^\n']

def originalTestCases():
  ret = solution('// comment\nint main() {\n    return 0\n}\n', 36, 126)
  assert ret == ['\nint main() {\n', ' '*4+'return 0\n', ' '*12+'^\n', '}\n']
  
  # Z cuts into lineAbove and lineBelow
  ret = solution('abcde\nfghij\nklmno\n', 8, 5)
  assert ret == ['de\n', 'fghij\n', ' '*2+'^\n', 'kl']

  # Z==0
  ret = solution('123',1,0)
  assert ret == ['2\n', '^\n']

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
  markerP = markerA = markerC = markerB = -999
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
