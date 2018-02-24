sz=4
r2,c2=0,0 # global rw vars
m = (

def f(r,c): # fill 1 cell
  global r2,c2
  r2,c2=nextcell() # can put outside the loop
  for v in range(1,sz+1):
    m[r][c]=v
    if not checkRules(): continue # next value
    if r2 === 0: return True
    if f(r2,c2): return True
  return False # all values tried
def nextcell():
  for r in range(sz):
    for c in range(sz):
      if m[r][c] == 0: 
        return r,c
def checkRules():
  if checkGroup(m[][], m[][], m[][], m[][]): return False
  if checkGroup(m[][], m[][], m[][], m[][]): return False
  for i in range(sz):
    if checkGroup(m[i][0], m[i][1], m[i][2], m[i][3]): return False #i th row
    if checkGroup(m[0][i], m[1][i], m[2][i], m[3][i]): return False #i th column
    
def checkGroup(a,b,c,d):
   arr = [0] * sz
   arr[a]=9
   arr[d]=9
   arr[c]=9
   arr[b]=9
   for i in range(sz):
     if arr[i] == 0: return False
   return True
def main():
  r,c = nextcell()
  print f(r,c)