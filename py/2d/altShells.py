height = 6
width = 7
color=0;
m = [[-1 for x in range(width)] for y in range(height)]
def get4(): # return indices of top left and bottom right corners
  minn = min(height,width)
  layers = (minn+1)/2
  global color
  color = (layers+1)%2 
  #return 1, 2,3 #height 4, 5 width
  return layers-1, height-layers, width-layers #height 5, 4 width
def paint(r,c):
  if 0<=r and r<height and 0<=c and c<width and m[r][c]!=color:
    msg = "r=%(r)d, c=%(c)d, existing =" % locals()
    assert m[r][c] ==-1, msg + str(m[r][c])
    m[r][c] =color
def dump():
  for r in xrange(len(m)):
    for c in xrange(width):
      print m[r][c], '\t',
    print
def work():
  global m, color
  TL, rBR, cBR = get4();
  for i in range(TL, -1, -1):
    color = 1-color
    for c in range(i, width-i):
      paint(i,c)
      paint(height-1-i, c)
    for r in range(i+1, height-1-i):
      paint(r,i)
      paint(r,width-i-1)
            
def main():
  work();
  dump();
main()
'''https://www.geeksforgeeks.org/create-a-matrix-with-alternating-rectangles-of-0-and-x/
Input: m = 3, n = 3
Output: Following matrix 
X X X
X 0 X
X X X

Input: m = 4, n = 5
Output: Following matrix
X X X X X
X 0 0 0 X
X 0 0 0 X
X X X X X

Input:  m = 5, n = 5
Output: Following matrix
X X X X X
X 0 0 0 X
X 0 X 0 X
X 0 0 0 X
X X X X X

Input:  m = 6, n = 7
Output: Following matrix
X X X X X X X
X 0 0 0 0 0 X
X 0 X X X 0 X
X 0 X X X 0 X
X 0 0 0 0 0 X
X X X X X X X 
'''
