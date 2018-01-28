/**
 * Requirement: count the number of K-complement pairs in a given int-array. if K/2 (for eg K/2=A)
 * is found once, then (A,A) counts as one pair. If A is found 2 times for example, 
 * then (1st A, 1st A) (1st A, 2nd A) (2nd A,  1st A), (2nd A, 2nd A) count as 4 pairs.
 * Requirement: worst run time should be O(N*logN)
 * 
 * Naive solution is O(N^2) -- check every pair.
 * 
 * To achieve O(N*logN), we must sort the input first. 
 * * No need to remember the original positions.
 * * array length is unchanged, with all the repeated numbers cluster together.
 * 
 * After sorting, binary search like http://www.java-examples.com/perform-binary-search-java-arraylist-example
 * * Suppose each pair is S/T.
 * * basically, for each Seeker (S) in the sorted list, find the Target (T) in the "right" subarray.
 * * any successful match would be saved in Result.
 */	
package com.codility.baml_fxo;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


public class Solution {
	public static void main(String[] args) {
    	int K = -10;
    	int[] A=new int[] {1, 8, -3, 0, 1, -7, 3, 3,3, -2, 4, 2147483647, 5};
		//int ret = new Solution().problem1(K,A);
		int ret = new Solution().problem3(-10,-1);
    	System.out.println(ret);
	}
	boolean isOverflow(int T, int K, int S) { //T = K-S hit overflow
		if (S>=0) return T>K;
		return T<K;
	}
    public int problem1(int K, int[] A) {
    	int ret = 0;
        List<Integer> li = new ArrayList<Integer>();
        for (int index = 0; index < A.length; index++)
        {
            li.add(A[index]);
        }
    	Collections.sort(li);//System.out.println(li);
    	boolean foundTwin = false; //found a pair of identical numbers that are K-complement!
    	for (int Seeker: li) {
    		int Target = K-Seeker;
    		if (isOverflow(Target, K, Seeker)) {
    			System.out.println("subtraction overflow!");
    			continue;
    		}
    		
    		int index = Collections.binarySearch(li,Target);
    		if (index >= 0 && li.get(index) == Target) {
    			int frq = Collections.frequency(li, Target);
    			System.out.println(Seeker + " found " + Target + " (" + frq + " times)");
    			if (Seeker == Target) {
    				foundTwin = true;
    				continue;
    			}
    			ret += frq; 
    		}
    	}
    	if (foundTwin) {
    		int Target = K/2;
			int frq = Collections.frequency(li, Target);
    		ret += frq*frq;
    	}
    	return ret;
    }
    
    /** 
     * Requirement: find all whole-square numbers within the closed range [A to B]
     * Requirement: worst case runtime should be at most O(sqrt(B))
     * 
     * @param A
     * @param B
     * @return how many whole-square numbers
     */
    public int problem3(int A, int B) {
    	if (A>B) {
    		System.err.println("A > B! Bad input");
    		return 0;
    	}
    	int ret=0;
    	if (B<0)
    		return 0; // none found
    	int last=(int)Math.sqrt(B);
    	System.out.println(last + " = last");

    	int first = 0; // if A is 0 or negative
    	if (A>=1)
    		first = (int)Math.ceil(Math.sqrt(A));
    	System.out.println(first + " = first");

    	ret = last-first+1;
    	return ret;
    }
}
