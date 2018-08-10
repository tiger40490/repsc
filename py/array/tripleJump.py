'''
todo: more tests
showcase 
'''
def solve1greedy(li): # O(NN)
  sz = len(li)
  isVerbose = sz < 99
  bln = [sz for _ in xrange(sz)] #BestLefNode records
  # bln[0] is unused and remains -1 or sz. If it were 0, that would mean that from Node #0 the leftmost node we can jump to is #0 .. nonsense
  #print bln
  
  isOver=False
  for i in xrange(sz):
    maxJ = li[i]
    # if maxJ = 3, then update bln[i+1,2,3...
    for destR in xrange(i+1, i+1+maxJ):
      if i<bln[destR]:
        bln[destR] = i
        assert bln[destR] < destR
      if destR == sz-1:
        print 'Game over: Entire journey starting from right end:'
        print li
        print bln
        node = i
        for cnt in xrange(1,sz):
          print 'to #',node,
          if node == 0: return cnt
            #print 'returning', cnt
          node = bln[node]
    if isVerbose: print i, ':', maxJ, '->', bln
  
def main():
  assert 2==solve1greedy([2,3,1,1,4])
main()
'''Req: https://bintanvictor.wordpress.com/2018/08/10/least-jumps-to-the-end-triple-jump/
Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents the maximum permitted jump length from that position.
'''
