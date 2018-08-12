'''Every empty cell should start a new stack frame. 
The only important function is fill1cell(). All other functions are simple, well-defined. Just be careful with the details.

showcase: return None by default, esp. for boolean functions
showcase: assert
'''
COLORS = 4 # this many colors, each represented by 1,2,3... till this value
UNFILLED_COLOR = COLORS+1
GAME_OVER = -1
Mat = [[UNFILLED_COLOR for _ in range(COLORS)] for _ in range(COLORS)]

def fill1cell(r,c): # fill 1 cell. Return True if game won
  #print 'entering fill1cell() with', r,c
  global Mat
  Mat[r][c]=8797060 
  rNext,cNext=findNextCell2fill() 
  for guess in range(1,COLORS+1):
    Mat[r][c]=guess
    if failedSomething(): continue # next guess
      
    # no violation of any rule
    if rNext == GAME_OVER: return True # this happens after entire board completed
    if fill1cell(rNext,cNext): 
      assert findNextCell2fill() == (GAME_OVER, GAME_OVER)
      return True
  Mat[r][c] = UNFILLED_COLOR # restore
  #return None i.e. False by default

def findNextCell2fill(): 
# simple, well-defined utility
# can't use global var. Every stack frame remembers the "cell-after-me"
  for r in range(COLORS):
    for c in range(COLORS):
      if Mat[r][c] == UNFILLED_COLOR: 
        return r,c
  return GAME_OVER, GAME_OVER
def failedSomething():
# simple, well-defined utility
  if failed1group(Mat[0][0], Mat[0][1], Mat[1][1], Mat[1][0]): return True
  if failed1group(Mat[0][2], Mat[0][3], Mat[1][3], Mat[1][2]): return True
  if failed1group(Mat[3][3], Mat[3][2], Mat[2][2], Mat[2][3]): return True
  if failed1group(Mat[3][0], Mat[3][1], Mat[2][1], Mat[2][0]): return True
  for i in range(COLORS):
    if failed1group(Mat[i][0], Mat[i][1], Mat[i][2], Mat[i][3]): return True 
    if failed1group(Mat[0][i], Mat[1][i], Mat[2][i], Mat[3][i]): return True
  #return None i.e. False by default
def failed1group(a,b,c,d): # four cell values must have no dupes except zeros
   assert 0<=a and a<=UNFILLED_COLOR
   assert 0<=b and b<=UNFILLED_COLOR
   assert 0<=c and c<=UNFILLED_COLOR
   assert 0<=d and d<=UNFILLED_COLOR
   #print "in failed1group():",a,b,c,d,
   cnt = {1:0, 2:0, 3:0, 4:0, UNFILLED_COLOR:0}
   cnt[a]+=1; cnt[b]+=1; cnt[c]+=1; cnt[d]+=1
   #print cnt
   for i in range(1,COLORS+1):
     if cnt[i] > 1: return True
  #return None i.e. False by default
def dump():
  for r in range(COLORS):
    print Mat[r]  
  print '--------'    
def init1mat():
  global Mat
  Mat[0][1]=2; Mat[0][3]=1; 
  Mat[1][2]=3; # Mat[1][]=; 
  Mat[2][1]=4; #Mat[2][]=; 
  Mat[3][0]=2; Mat[3][2]=1; 
def init2mat():
  global Mat
  Mat[0][0]=2; Mat[0][3]=1; 
  Mat  [1][2]=4; # Mat[1][]=; 
  Mat [2][1]=2; #Mat[2][]=; 
  Mat[3][0]=3; #Mat[3][2]=4; 
def init():
  global Mat
  Mat  [0][2]=2; #Mat[0][3]=1; 
  Mat[1][0]=2; Mat[1][3]=1; 
  Mat[2][0]=3; #Mat[2][]=; 
  Mat [3][1]=4; #Mat[3][2]=4; 
def main():
  init()
  dump()
  rNext,cNext=findNextCell2fill()
  if fill1cell(rNext,cNext): 
    dump()
  else: print 'Impossible'
main()
