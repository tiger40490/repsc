//$Id$
package com.tanbinFIX.clientside.state;

import java.util.LinkedHashMap;
import java.util.Map;

import com.tanbinFIX.bothside.MyConst;
import com.tanbinFIX.bothside.format.FIXFormatter;
import com.tanbinFIX.bothside.format.FIXMsgField;


public class NewOrderPending extends AbstractSate {

	@Override
	public Map<FIXMsgField, String> getNextOutgoingMsgMap(int seq) {
		Map<FIXMsgField,String> m = 
			new LinkedHashMap<FIXMsgField,String>(); 
		m.put(FIXMsgField.MsgType, "D");
		m.put(FIXMsgField.MsgSeqNum, seq + "");
		m.put(FIXMsgField.SenderCompID, MyConst.SENDER_COMP_ID);
		m.put(FIXMsgField.TargetCompID, MyConst.TARGET_COMP_ID);
		m.put(FIXMsgField.OrderQty, "1000");
		m.put(FIXMsgField.TimeInForce, "1");
		m.put(FIXMsgField.OrdType, "1");
		m.put(FIXMsgField.ClOrdID, "ORD10001");
		m.put(FIXMsgField.Symbol, "HPQ");
		m.put(FIXMsgField.Side, "1");
		m.put(FIXMsgField.HandlInst, "2");
		m.put(FIXMsgField.TransactTime, FIXFormatter.getCurrentTime());
		
		// other fields omitted....

		return m;
	}
}
