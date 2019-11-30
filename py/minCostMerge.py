'''

'''
import bisect

def solution(li):
  cumcost=0
  #removing from end of vector. Note a linked list would be more efficient
  li.sort(reverse=True) 
  while len(li)>=2:
    sum = ( li[-1]+li[-2] )
    del li[-1]
    del li[-1]
    cumcost += sum
    bisect.insort(li, sum)
    print li
  print cumcost 
  return cumcost
def main():
  assert 1700 == solution([100, 250, 1000])
main()
'''Req: Given N sorted arrays to be merged into one, find the mininum cost merging strategy.
Each pair-wise merge has a cost = sum of both lengths.
'''