'''
showcase 
'''
def solve1greedy(li): # O(NN)
  sz = len(li)
  isVerbose = sz < 99
  bln = [sz for _ in xrange(sz)] #BestLefNode records
  # bln[0] is unused and remains -1 or sz. If it were 0, that would mean that from Node #0 the leftmost node we can jump to is #0 .. nonsense
  #print bln
  
  # now update bln:
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
'''Req: Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents the maximum permitted jump length from that position.

Typical greedy algorithm. I will jump leftward.

Suppose there are N=99 nodes. I will pre-scan the N nodes to build a shadow array of integer records, each a BestLefNode. (The first record is unused ... can put in -1)

If BestLefNode[44] == 33, it means that based on known data the left-most (furthest) node we can jump to from Node #44 is Node #33. 

When we visit Node #7 during the scan, we will update BestLefNode record #8 onwards. 

As soon as we update BestLefNode[N-1] i.e. right-most record, we can exit the initial scan since the optimal solution is now available.

Once the BestLefNode records are built, I simply follow them! For example, if rightmost BestLefNode has value #88, that means the furthest node we can reach from the right end is Node #88, so we will jump to #88 and then check the best destination from #88
'''