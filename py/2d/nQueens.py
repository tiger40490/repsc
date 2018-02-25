SZ=5
UNFILLED = '|'
Q = 'Q'
Mat = [[UNFILLED for _ in range(SZ)] for _ in range(SZ)]

def p(r): # place the queue on row r, assuming all previous rows are done
  #if r == SZ: return True
  global Mat
  for c in range (0, SZ):
    Mat[r][c] = Q
    if failed(): 
      Mat[r][c] = UNFILLED
      continue
    if r == SZ-1: 
      print 'solution found'
      dump()
      return True
    ok = p(r+1)
    if ok: return True
    else: 
      Mat[r][c] = UNFILLED
      continue # not needed, but nice documentation
  Mat[r][c] = UNFILLED
  # return False by default

def failed1group(cells):
  #dump(); print 'checking', cells  
  sum=0
  for r,c in cells:
    if 0<=r and r<SZ and 0<=c and c<SZ:
      if Mat[r][c] == Q: 
        sum +=1
        if sum > 1: return True
  # return False by default    
def failed():
  for c in range(0,SZ):
    if failed1group([(r,c) for r in range(0,SZ)]): 
      return True
  #check all diagnal  
  for dif in range(2-SZ,SZ-1): 
    if failed1group([(r,r+dif)   for r in range(0,SZ)]):
      return True          
  for sum in range(1,2*SZ-2): 
    if failed1group([(sum-c, c)   for c in range(0,SZ)]):
      return True      
    
def dump():
 for r in range(0,SZ):
   print ' '.join(Mat[r])

def main():
  ok = p(0)
  if not ok: 
    print 'impossible'

main()    