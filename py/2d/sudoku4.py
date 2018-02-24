sz=4
Mat = [[0 for _ in range(sz)] for _ in range(sz)]

def f(r,c): # fill 1 cell. Return True if game won
  print 'entering f() with', r,c
  global Mat
  Mat[r][c]=87 
  rNext,cNext=findNextCell2fill() 
  for guess in range(1,sz+1):
    Mat[r][c]=guess
    #print 'trying:'; dump()
    if failedSomething(): continue # next guess
    #print ' ... passed:)'
    if rNext < 0: return True
    if f(rNext,cNext): return True
  Mat[r][c] = 0 # restore
  return False # all values tried

def findNextCell2fill(): # return 0 to indicate no more
  for r in range(sz):
    for c in range(sz):
      if Mat[r][c] == 0: 
        return r,c
  return -1,-1
def failedSomething():
  if groupFailed(Mat[0][0], Mat[0][1], Mat[1][1], Mat[1][0]): return True
  if groupFailed(Mat[0][2], Mat[0][3], Mat[1][3], Mat[1][2]): return True
  if groupFailed(Mat[3][3], Mat[3][2], Mat[2][2], Mat[2][3]): return True
  if groupFailed(Mat[3][0], Mat[3][1], Mat[2][1], Mat[2][0]): return True
  for i in range(sz):
    if groupFailed(Mat[i][0], Mat[i][1], Mat[i][2], Mat[i][3]): return True #i th row
    if groupFailed(Mat[0][i], Mat[1][i], Mat[2][i], Mat[3][i]): return True #i th column
   # return False by default  
def groupFailed(a,b,c,d): # 
   assert 0<=a and a<=4
   assert 0<=b and b<=4
   assert 0<=c and c<=4
   assert 0<=d and d<=4
   #print "in groupFailed():",a,b,c,d,
   cnt = {0:0, 1:0, 2:0, 3:0, 4:0}
   cnt[a]+=1; cnt[b]+=1; cnt[c]+=1; cnt[d]+=1
   #print cnt
   for i in range(1,sz+1):
     if cnt[i] > 1: return True
   # return False by default
def dump():
  for r in range(sz):
    print Mat[r]  
  print '--------'    
def init():
  global Mat
  Mat[0][1]=2; Mat[0][3]=1; 
  Mat[1][2]=3; # Mat[1][]=; 
  Mat[2][1]=4; #Mat[2][]=; 
  Mat[3][0]=2; Mat[3][2]=1; 
def init2():
  global Mat
  Mat[0][0]=2; Mat[0][3]=1; 
  Mat  [1][2]=4; # Mat[1][]=; 
  Mat [2][1]=2; #Mat[2][]=; 
  Mat[3][0]=3; #Mat[3][2]=4; 
def main():
  init2()
  dump()
  rNext,cNext=findNextCell2fill()
  print f(rNext,cNext)
  dump()
  #for i in range(2,3):
  #  print groupFailed(Mat[i][0], Mat[i][1], Mat[i][2], Mat[i][3])   
main()
'''Every empty cell should start a new stack frame
'''