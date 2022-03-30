'''
showcase 
'''
def solve1greedy(li): # O(NN)
  sz = len(li)
  isVerbose = sz < 99
  bln = [sz for _ in xrange(sz)] #BestLeftsideNode records
  # bln[0] is unused and remains -1 or sz. If it were 0, it would mean that from Node #0 the leftmost node reachable (by a jump) is #0 .. nonsense
  if isVerbose: print 'BestLeftsideNode array =', bln
  
  for me in xrange(sz-1): # I'm a node and "me" is my index. Last node's value is ignored
    maxJ = li[me]
    # if maxJ = k, then update bln[me+1], bln[j+2], bln[j+3] .. bln[j+k]
    for reachableNodeOnMyRight in xrange(me+1, me+1+maxJ):
      if me<bln[reachableNodeOnMyRight]:
        #suppose me is 11 and bln[33] is now 22, meaning up to now the leftmost reachable node from #33 is #22, but now we know #11 is reachable too, so update!
        bln[reachableNodeOnMyRight] = me
        assert bln[reachableNodeOnMyRight] < reachableNodeOnMyRight, "NodeA's BestLeftsideNode must be on the left of NodeA"
      if reachableNodeOnMyRight == sz-1: #last node
        if isVerbose: 
          print 'Game over! Here is the Entire journey starting from right end:'
          print li, '= original array'
          print bln,'= BestLeftsideNode records'
        node = me
        for cnt in xrange(1,sz):
          if isVerbose: print 'to #',node,
          if node == 0: return cnt
            #print 'returning', cnt
          node = bln[node]
    if isVerbose: print me, ':', maxJ, '->', bln
  
def main():
  assert 4==solve1greedy([1,1,1,1,9])
  assert 2==solve1greedy([2,3,1,1,4])
  assert 3==solve1greedy([5,4,1,3,1,1,9,1,6,1,1,1,99])
  assert 3==solve1greedy([2,5,3,1,1,1,7,1,1,1,99])
main()
'''Req: https://bintanvictor.wordpress.com/2018/08/10/least-jumps-to-the-end-triple-jump/
Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents the maximum permitted jump length from that position.
'''
