m = list() 

def test1():
  global m
  m.append([1,1,1,1])
  m.append([1,1,1,1])
  m.append([1,1,1,1])
def test2():
  global m
  m.append([1,1,0,1])
  m.append([1,1,1,1])
def start(r,c): 
  '''every time we find a path, inc'''
  global finalCnt
  if m[r][c]==0: #dead end
    return
  if r < height-1:
    start(r+1, c)
  if c < width-1:
    start(r, c+1)
    
  if r == height-1 and c == width-1:
    finalCnt += 1
    print 'incremented finalCnt to', finalCnt
def work(setup1test):
  global m, width, height, finalCnt
  m = list()
  setup1test()
  height = len(m)
  width = len(m[0])
  finalCnt=0;
  start(0,0)
def main():
  work(test1)
  work(test2)
main()
'''Req: See pdf in the same dir. Here are some key points:

Consider a maze mapped to a matrix with an upper left corner at coordinates (row, column) = (0, 0). Any movement must be in increasing row or column direction. You must determine the
number of distinct paths through the maze. You will always start at position (0, 0), the top left, and end up at (max(row), max(column)), the bottom right. 

1 1 0 1
1 1 1 1 

As an example, consider the above diagram where 1 indicates an open cell and 0 indicates blocked. You can only travel through open cells, so no path can go through the cell
at (0, 2). There are two distinct paths to the goal.

The function must return the number of paths through the matrix, modulo (10^9 + 7).

1 <= n, m <= 1000

--Analysis:
Better use a 64-bit int

I see a binary tree, where each node is a cell. Cell (0,0) has down/left node (1,0) + right node (0,1). I feel this is similar to the classic problem "count paths between 2 nodes in a binary tree"

Brute force: I implemented something like a DFT but it was too slow with some test cases

From any cell, we can compute how many distinct paths. Save it in a lookup{cell -> cnt}

'''