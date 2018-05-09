package com.hackerrank.buyBuySell;
import java.util.*;
import static java.lang.System.*;

class BuyBuySell{
    public static void main(String [] args) throws Exception    {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(int t = 0; t < T; t++) {
        	int N = sc.nextInt();
        	List<Integer> li = new ArrayList<Integer>(N);
        	for (int n=0; n<N; ++n) {
        		int b = sc.nextInt();
        		li.add(b);
        	}
            play(li);
        }
        sc.close();
    }

	private static void play(final List<Integer> li) {
		int holding=0;
		for (int i=0; i<li.size()-1; ++i) {
			final int level = li.get(i);
			if (level <= li.get(i+1)) {//"=" is prudent
				out.println("buy 1 share @ $" + level);
				++holding;
			}else if (holding >0) {
				out.println("sell " + holding + " shares @ $" + level);			
				holding=0;
			}
		}
		if (holding >0) {
			final int lastLevel=li.get(li.size()-1);
			final int prevLevel=li.get(li.size()-2);
			assert (prevLevel<=lastLevel);
			out.println("last sell " + holding + " shares @ $" + lastLevel);
		}
		out.println();
	}
}/*Requirement: given a time series of price points, you are allowed to buy one share 
at any point, or sell up to all shares you hold. No short sell. Maximize profit.

I probably mis-understood the PIMCO hacker rank requirement since I failed most hidden tests.

Overall, I liked this little challenge.
*/