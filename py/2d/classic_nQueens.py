'''The only important function is placeOnRow()

showcase: deepcopy of 2D array
'''
from copy import copy, deepcopy
UNFILLED = '|'
Q = 'Q'
SZ=0
Mat = list()
sols = list()

def placeOnRow(r): # place the queue on row r, assuming all previous rows are done
  for c in range (0, SZ):
    Mat[r][c] = Q
    if failedSomething(): 
      Mat[r][c] = UNFILLED
      continue
    if r == SZ-1: #print 'solution found:'; dump(Mat)
      sols.append(deepcopy(Mat))
      Mat[r][c] = UNFILLED
      continue
    placeOnRow(r+1)
    Mat[r][c] = UNFILLED
  # return None by default

def failed1group(cells):
  #dump(); print 'checking', cells  
  sum=0
  for r,c in cells:
    if 0<=r and r<SZ and 0<=c and c<SZ:
      if Mat[r][c] == Q: 
        sum +=1
        if sum > 1: return True
  # return False by default    
def failedSomething():
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
    
def dump(m):
  for r in range(0,SZ):
    print ' '.join(m[r])
  print '------------'
def countSol(queens):
  global SZ, sols
  SZ=queens
  sols[:]=[]
  Mat[:]=[]
  Mat.extend([[UNFILLED for _ in range(SZ)] for _ in range(SZ)])
  placeOnRow(0)  
  repeat=3
  header =' v ' * repeat
  footer =' ^ ' * repeat
  print header, len(sols), 'solutions found', header
  for mat in sols:
    dump(mat)
  print footer, len(sols), 'solutions found', footer
  return len(sols)
def main():
  assert 10 == countSol(5)
  assert 4  == countSol(6)
  assert 40 == countSol(7)
  assert 92 == countSol(8)
main()    
