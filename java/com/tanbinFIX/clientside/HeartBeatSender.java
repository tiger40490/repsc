//$Id$
package com.tanbinFIX.clientside;

import java.io.Closeable;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

import com.tanbinFIX.bothside.MyConst;
import com.tanbinFIX.bothside.OutStreamWrapper;
import com.tanbinFIX.bothside.format.FIXFormatter;
import com.tanbinFIX.bothside.format.FIXMsgField;

public class HeartBeatSender extends Thread implements Closeable {
	/**
	 * This is an experiment with timer. 
	 * 
	 * should be replaced with scheeduled thread pool as in Destroyer.java
	 */
	private final Timer timer = new Timer();
	private final OutStreamWrapper out;
	private final ClientSession session;

	public HeartBeatSender(int mills, OutStreamWrapper out, ClientSession s) {
		this.session = s;
		this.out = out;
		timer.scheduleAtFixedRate(new SendHeartBeatTask(), mills, mills);
	}

	private class SendHeartBeatTask extends TimerTask implements MyConst {
		public void run() {
			// if (true) return;
			if (!session.isConnected())
				return;
			Map<FIXMsgField, String> m = new LinkedHashMap<FIXMsgField, String>();
			m.put(FIXMsgField.MsgType, "0");// heartbeat
			m.put(FIXMsgField.MsgSeqNum, session.incrementAndGetSeq() + "");
			m.put(FIXMsgField.SenderCompID, MyConst.SENDER_COMP_ID);
			m.put(FIXMsgField.TargetCompID, MyConst.TARGET_COMP_ID);

			String toServer = FIXFormatter.mapToFIXString(m);
//			System.out.println("\t sending heart beat");
			out.println(toServer, "sending heart beat");
		}
	}

	@Override
	public void close() {
		timer.cancel();
	}
}
