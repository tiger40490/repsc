width, height = 0,0
m = list() 

def print1(r,j): # simple utility
  if 0<=r and r<height and 0<=j and j<width:
    print m[r][j], '\t',
	
def work():
  maxCR = max(width, height)
  for i in xrange(width + height -1):
    for j in xrange(maxCR):
     r = i - j
     if r < 0 or j > width: break
     print1(r,j)
    print

def populate():
  global m, width, height
  m.append([1,2,3,4])
  m.append([5,6,7,8])
  m.append([9,10,11,12])
  m.append([13,14,15,16])
  m.append([17,18,19,20])
  height = len(m)
  width = len(m[0])
  
def main():
  populate()
  work()
  for r in xrange(len(m)):
    for c in xrange(width):
      print m[r][c], '\t',
    print
   
main()
'''https://www.geeksforgeeks.org/zigzag-or-diagonal-traversal-of-matrix/

    1     2     3     4
    5     6     7     8
    9    10    11    12
   13    14    15    16
   17    18    19    20
Diagonal printing of the above matrix is

    1
    5     2
    9     6     3
   13    10     7     4
   17    14    11     8
   18    15    12
   19    16
   20
'''