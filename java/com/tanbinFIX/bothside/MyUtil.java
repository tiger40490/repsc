//$Id$
package com.tanbinFIX.bothside;

public class MyUtil {
	public static boolean hasText(String s) {
		boolean noText = s == null || s.isEmpty();
		return ! noText;
	}
}
