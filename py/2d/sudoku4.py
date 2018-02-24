sz=4
#r2,c2=0,0 # global rw vars
m = [[0 for _ in range(sz)] for _ in range(sz)]

def f(r,c): # fill 1 cell. Return True if game won
  global m
  m[r][c]=-1 # tmp
  r2,c2=nextCell2fill() # no need to get this every time
  for v in range(1,sz+1):
    m[r][c]=v
    dump()
    if failed(): continue # next value
    if r2 < 0: return True
    if f(r2,c2): return True
  return False # all values tried
def nextCell2fill(): # return 0 to indicate no more
  for r in range(sz):
    for c in range(sz):
      if m[r][c] == 0: 
        print 'nextCell2fill returning', r,c
        return r,c
  return -1,-1
def failed():
  if groupFailed(m[0][0], m[0][1], m[1][1], m[1][0]): return True
  if groupFailed(m[0][2], m[0][3], m[1][3], m[1][2]): return True
  if groupFailed(m[3][3], m[3][2], m[2][2], m[2][3]): return True
  if groupFailed(m[3][0], m[3][1], m[2][1], m[2][0]): return True
  for i in range(sz):
    if groupFailed(m[i][0], m[i][1], m[i][2], m[i][3]): return True #i th row
    if groupFailed(m[0][i], m[1][i], m[2][i], m[3][i]): return True #i th column
    
def groupFailed(a,b,c,d): # 
   assert 0<=a and a<=4
   assert 0<=b and b<=4
   assert 0<=c and c<=4
   assert 0<=d and d<=4
   #print "in groupFailed():",a,b,c,d,
   cnt = {0:0, 1:0, 2:0, 3:0, 4:0}
   cnt[a]+=1
   cnt[b]+=1
   cnt[c]+=1
   cnt[d]+=1
   #print cnt
   for i in range(1,sz):
     if cnt[i] > 1: return True
   # return False by default
def dump():
  for r in range(sz):
    print m[r]  
  print '--------'    
def main():
  r,c = nextCell2fill()
  print f(r,c)
main()
'''Every empty cell should start a new stack frame
'''