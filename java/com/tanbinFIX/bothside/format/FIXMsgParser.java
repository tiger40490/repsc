//$Id$
package com.tanbinFIX.bothside.format;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import com.tanbinFIX.bothside.MyConst;

public class FIXMsgParser implements MyConst {

	private static final int MAX_FIX_TAG = 400;

	/**
	 * Parsing to array is faster than parsing to a HashMap<enum,String>
	 */
	public static ArrayList<String> quickParse(String fromServer) {
		ArrayList<String> ret = new ArrayList<String>(Collections.nCopies(
			MAX_FIX_TAG, (String) null));
		for (String pair : fromServer.split(SOH)) {
			// System.out.println(pair);
			String[] tmp = pair.split("=");
			if (tmp.length != 2) { 
				// for this test, server can send invalid format
				continue;
			}
			int tag = Integer.parseInt(tmp[0]);
			ret.set(tag, tmp[1]); //treat ArrayList as array -- efficient
		}
		return ret;
	}

	@Deprecated
	private static Map<?, String> parseNotInUse(String fromServer) {
		Map<? super Object, String> ret = new HashMap<Object, String>();

		String[] pairs = fromServer.split(SOH);
		for (String pair : pairs) {
			// System.out.println(pair);
			String[] tmp = pair.split("=");
			if (tmp.length != 2) { // for this test, server can send invalid
									// format
				continue;
			}
			String tag = tmp[0];
			ret.put(tag, tmp[1]);
		}
		return ret;
	}
}
