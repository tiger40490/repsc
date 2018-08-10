'''Req: Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length from that position.

I will jump leftward.

Suppose there are N=99 nodes. I will scan the N nodes just once to build a shadow array of BestDestinations. (The first element is unused ... can put in -1)

If BestDestination[44] == 33, it means that based on known data the left-most (furthest) node we can jump to from Node #44 is Node #33. 

When we visit Node #7 of the scan, we will update BestDestinations record #8 onwards. 

As soon as we update BestDestination[N-1] i.e. right-most record, we can exit the initial scan since.

Once the BestDestinations are built, I simply follow it! For example, if rightmost BestDestination has value #88, that means the furthest node we can reach from the right end is Node #88, so we will jump to #88 and then check the best destination from #88
'''