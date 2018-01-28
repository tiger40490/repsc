//$Id$
package com.tanbinFIX.clientside.state;

import java.util.LinkedHashMap;
import java.util.Map;

import com.tanbinFIX.bothside.MyConst;
import com.tanbinFIX.bothside.format.FIXMsgField;

public class LogonPending extends AbstractSate {
	@Override
	public Map<FIXMsgField, String> getNextOutgoingMsgMap(int seq) {
		Map<FIXMsgField, String> m = new LinkedHashMap<FIXMsgField, String>();
		m.put(FIXMsgField.MsgType, "A");// logon
		m.put(FIXMsgField.MsgSeqNum, seq + "");
		m.put(FIXMsgField.SenderCompID, MyConst.SENDER_COMP_ID);
		m.put(FIXMsgField.TargetCompID, MyConst.TARGET_COMP_ID);
//		System.out.println("\t sending logon");
		return m;
	}

}
