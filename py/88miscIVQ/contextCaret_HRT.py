'''
todo: reorg code
if Z is beyond lineAbove, then that line is printed.
if Z cust into part of lineAbove, then ... look at the eg
if Z cuts into lineCtr on the left, then there will be no lineAbove
if Z is 0, then special handling?
'''

def lineA(multiLineCode,errPos,Z, vec):
  # print lineAbove 
  # what if markerP is -999?
  if markerA < 0: return #nothing to print for lineAbove
  ret = multiLineCode[max(markerP, errPos-Z) : markerA+1]
  if len(ret) == 0: return
  print ret[:-1] + '<-- lineA'
  vec.append(ret)

def lineB(multiLineCode,errPos,Z, vec):
# what if markerB is -999999?
  if markerB < 0: return # nothing to print for lineBelow
  print 'in lineB()', markerC, errPos+Z
  if errPos+Z <= markerC: return # the Z chars afer errPos is before or up to the newline
  ret = multiLineCode[markerC+1 : 1+min(markerB, errPos+Z)]
  if len(ret) == 0: return  
  print ret[:-1] + '<-- lineB'
  vec.append(ret)

def lineC(multiLineCode,errPos,Z, vec):
  if markerC > 0:
    distB = abs(errPos-markerB) #not needed in this lineC()
    distA = abs(errPos-markerA) 
    distC = abs(errPos-markerC)
    #print 'distA,distC ..', distA,distC
    if Z >= distA and Z >= distC: 
      print 11111111
      vec.append( multiLineCode[markerA+1: markerC+1] )
      tmp = (' ' * (distA-1)) + '^\n'
      if vec[-1][-1] != '\n': tmp = '\n'+tmp
      vec.append(tmp)
    if Z >= distA and Z < distC:
      print 22222222
      vec.append(  multiLineCode[markerA+1 : Z+errPos+1] )
      assert vec[-1][-1] != '\n'
      vec.append(  '\n'+ (' '* (distA-1)) + '^\n' )
    if Z < distA and Z < distC:
      print 3333333
      vec.append(  multiLineCode[errPos-Z: errPos+Z+1]+'\n' )
      vec.append(  (' ' *Z) + '^\n' )
    if Z < distA and Z >= distC:
      print 4444444
      print markerC+1
      vec.append(  multiLineCode[errPos-Z: markerC+1] )
      tmp = (' ' *min(errPos,Z)) + '^\n'
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

  ret = solution('012345678\n012c4',13, 5)
  assert ret == ['8\n', '012c4', '\n   ^\n']
  
  ret = solution('012345678\n012c4',13, 2)
  assert ret == ['12c4', '\n  ^\n']
  

def originalTestCases():
  ret = solution('// comment\nint main() {\n    return 0\n}\n', 36, 126)
  assert ret == ['\nint main() {\n', ' '*4+'return 0\n', ' '*12+'^\n', '}\n']
  
  # Z cuts into lineAbove and lineBelow
  ret = solution('abcde\nfghij\nklmno\n', 8, 5)
  assert ret == ['de\n', 'fghij\n', ' '*2+'^\n', 'kl']

  # Z==0
  ret = solution('123',1,0)
  assert ret == ['2\n', '^\n']

def solution(multiLineCode,errPos,Z):
  vec = list()
  find3markers(multiLineCode,errPos)
  lineA(multiLineCode,errPos,Z, vec)
  lineC(multiLineCode,errPos,Z, vec)
  lineB(multiLineCode,errPos,Z, vec)
  print vec
  return vec

def find3markers(multiLineCode,errPos):
  global markerP, markerC, markerA, markerB
  markerP = markerA = markerC = markerB = -999999999
  # locate the 3 nlMarkers and find the distance to errPos
  if multiLineCode[-1] != '\n': multiLineCode=multiLineCode+'\n'
  newlines = list()
  for pos,char in enumerate(multiLineCode):
    if char == '\n': 
      sz = len(newlines)
      if pos >= errPos: # 
        markerC = pos # markerC is the position of the newline_following_Y
        if sz >= 2: markerP = newlines[-2]
        if sz >= 1: markerA = newlines[-1] 
        tmp = multiLineCode.find('\n', pos+1)
        if (tmp != -1): markerB = tmp
        print 'returning with markerP, markerA, markerC, markerB .. ', markerP, markerA, markerC, markerB
        return 3
      newlines.append(pos)
  raise Exception('Since the final char is always newline, we should definitely have a markerC.')

testAll()
''' req: https://btv-gz.dreamhosters.com/3005/careterrorwithcontext-sachin-hrt/
'''
