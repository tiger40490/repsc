//$Id$
package com.tanbinFIX.clientside.state;

import java.util.Date;
import java.util.Map;

import com.tanbinFIX.bothside.OutStreamWrapper;
import com.tanbinFIX.bothside.format.FIXFormatter;
import com.tanbinFIX.bothside.format.FIXMsgField;

public abstract class AbstractSate {
	final long started= new Date().getTime();; // stateTransitionStart
	private volatile boolean isSent = false;

	/**
	 * The next outgoing msg depends on the current State
	 */
	public abstract Map<FIXMsgField, String> getNextOutgoingMsgMap(int seq);

	synchronized public void send(OutStreamWrapper out, int seqForOutgoingMsg, String labelForLogging) {
		if (isSent) {
			// it's dangerous to resend a New Order Single.
			// Exchange may treat it as another order!
			return;
		}
		String toServer = FIXFormatter.mapToFIXString(getNextOutgoingMsgMap(seqForOutgoingMsg));
//		System.out.println("Client: " + toServer);
		out.println(toServer, labelForLogging);
		this.isSent = true;
	}
}
