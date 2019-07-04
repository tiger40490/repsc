# Can this algo apply to a linked list? I guess so
import random
arr=[8,1,2,8, 33,9,33,4,5,6,7]
arr.extend(random.sample(xrange(-99, 100), 19))

def dump(le, ri, note=''):
  print '-- dumping between positions', le, ri, note
  print arr[le : ri+1]
  
def swap(p1, p2):
  tmp = arr[p1]
  arr[p1] = arr[p2]
  arr[p2] = tmp
def partR(le, ri): #based on https://leetcode.com/problems/kth-largest-element-in-an-array/discuss/60294/Solution-explained
# not tested
  pivot = arr[ri]
  back=le
  for front in xrange(le, ri):
    if arr[front] <= pivot : # throw low values back
      swap(back,front)
      back += 1
  assert arr[back] > pivot
  swap(back,ri) # anchor the pivot 
  return back
''' private int partition(int[] nums, int lo, int hi) {
        int pivot = nums[hi];
        int i = lo;
        for (int j = lo; j < hi; j++) {
            if (nums[j] <= pivot) {
                swap(nums, i, j);
                i++;
            }
        }
        swap(nums, i, hi);
        return i;
    }
'''
def partL(le, ri):
'''Regard left most object as pivot.
shift it to its anchor position such that 
* all objects lower than pivot are on its left
* all objects higher than pivot are on its right
return the anchor position'''
  pivot=arr[le]
  anchor=le
  for i in range(le+1, ri+1):
    if arr[i] >= pivot: continue
    swap(anchor+1, i)
    swap(anchor+1, anchor)
    anchor += 1
  return anchor

def qsort(le, ri):
  length = ri-le+1
  if length <= 1: return
  anchor = partL(le, ri)
  dump(le, ri, ', anchor = %d' %anchor)
  qsort(le, anchor-1)
  qsort(anchor+1, ri)
  dump(le, ri, ', after sorting both sections')
  
def main():
  qsort(0, len(arr)-1)
  for i in range(len(arr)-1):
    assert arr[i] <= arr[i+1] # verify
main()
