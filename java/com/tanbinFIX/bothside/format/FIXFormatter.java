//$Id$
package com.tanbinFIX.bothside.format;

import java.text.SimpleDateFormat;
import java.util.Formatter;
import java.util.HashMap;
import java.util.Map;

import com.tanbinFIX.bothside.MyConst;

public class FIXFormatter {
	public static final SimpleDateFormat DATE_FORMAT = new SimpleDateFormat(
			"yyyyMMdd-HH:mm:ss");

	// public static void main(String[] args) {
	// // System.out.printf("%03d", 11);
	// HashMap<?, String> msg = getTestMsgMap();
	// String fixString = mapToFIXString(msg);
	// System.out.println(fixString);
	// }

	public static String getCurrentTime() {
		return DATE_FORMAT.format(new java.util.Date());
	}

	public static String mapToFIXString(Map<FIXMsgField, String> msgMap) {
		StringBuilder sb = new StringBuilder();
		for (Map.Entry<FIXMsgField, String> entry : msgMap.entrySet()) {
			sb.append(entry.getKey().tag).append("=").append(entry.getValue());
			sb.append(MyConst.SOH);
		}
		sb.append(FIXMsgField.SendingTime.tag).append("=").append(
			getCurrentTime());
		sb.append(MyConst.SOH);

		// hardcode heartbeat interval
		sb.append(FIXMsgField.HeartBtInt.tag).append("=30");
		sb.append(MyConst.SOH);

		// hardcode encryption method
		sb.append(FIXMsgField.EncryptMethod.tag).append("=0");
		sb.append(MyConst.SOH);

		sb.insert(0, FIXMsgField.BeginString.tag + "=FIX.4.2" + MyConst.SOH
				+ FIXMsgField.BodyLength.tag + "=" + sb.length() + MyConst.SOH);
		return appendCheckSum(sb.toString());
	}

	private static String appendCheckSum(String front) {
		int checkSum = 0;
		for (char aChar : front.toCharArray()) {
			checkSum += (int) aChar;
		}
		String format = front + FIXMsgField.CheckSum.tag + "=%03d"
				+ MyConst.SOH;
		return String.format(format, checkSum % 256);
	}

	private static HashMap<Object, String> getTestMsgMap() {
		HashMap<Object, String> msgHM = new HashMap<Object, String>();
		msgHM.put(FIXMsgField.SenderCompID, MyConst.SENDER_COMP_ID);
		msgHM.put("Account", "12345678");
		// msgHM.put("AccruedInterestAmt", "100.89");
		// msgHM.put("AccruedInterestRate", "0.02");
		// msgHM.put("AdvId", "999");
		// msgHM.put("AdvRefID", "888");

		return msgHM;
	}
}