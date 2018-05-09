/* showcase memoization, hopefully to avoid revisiting any node
 * todo: more tests
*/
package com.hackerrank.mazePath;
import java.util.*;
import static java.lang.System.*;

class Solution{
    public static void main(String [] args) throws Exception    {
        Scanner sc = new Scanner(System.in);
        R = 3;//sc.nextInt(); 
        C = 4;//sc.nextInt();
        int[][] m = new int[R][C];
        for(int r = 0; r < R; r++) {
            for(int c = 0; c < C; c++) {
            	m[r][c] = 1;//sc.nextInt();
            }
        }
    	out.println(numberOfPaths(m));
    	sc.close();
    }
	static int paths=0, R=0, C=0;
	static int[][] alreadyCounted ;
    static int numberOfPaths(final int[][] m) {//required method signature    	
    	R = m.length; C = m[0].length;
        if (R==1 && C==1) return 1;
        alreadyCounted = new int[R][C]; /*initialized to zeros. 
See https://stackoverflow.com/questions/5391441/creating-an-int-array-filed-with-zeros-in-java */
        paths = recurs(m, 0,0);
        System.out.println(paths);
    	return paths;
    }
    /**
     * @param m
     * @param r
     * @param c
     * @return -- how many paths starting from [r][c]
     */
	static int recurs(int[][] m, int r, int c) {
        System.out.println("recur "+r+"/"+c);		
		if (alreadyCounted[r][c] > 0) {
			return alreadyCounted[r][c];
		}else if( alreadyCounted[r][c] == -1) {
			return 0;
		}
		
		int ret=0;
		
		char res = check(m, r+1, c);
		if (res == 'g') ret += recurs(m, r+1, c);
		else if (res == 1) ret++; //no need to recurse into that cell on the right
		//the above logic may not be correct!
		
		res = check(m, r, c+1);
		if (res == 'g') ret +=recurs(m, r, c+1);
		else if (res == 1) ret++;
		
		System.out.println(r+"/"+c+" recurse() returns "+ ret);
		if (ret == 0) { //use -1 to mark a cell as "dead"
			alreadyCounted[r][c] = -1;	
		}else {
			alreadyCounted[r][c] = ret;
		}
		return ret;
	}
	/**Some may prefer a boolean function, but a char helps instrumentation
	 */
	static private char check(int[][] m, int r, int c) {
        System.out.println("checking "+r+"/"+c);
		if (r >= R) return 'R'; 
		if (c >= C) return 'C';
		if (m[r][c] == 0) {
			alreadyCounted[r][c] = -1; //needed?
			return '0'; //blocked
		}
		if (r==R-1 && c==C-1) return 1; 
		return 'g'; //there are potentially multiple paths from [r][c]
	}
}/*requirement: in a binary matrix, every one represents a passage, 
and zero a wall. You 
can only move right or down. From origin to the bottom right corner 
(destination), count how many distinct paths there are.

The PIMCO Hacker rank set-up restricts us to use static...
*/