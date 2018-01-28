//$Id$
package com.tanbinFIX.clientside;

import java.io.Closeable;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * #1 job is to control the 2 seq num.
 * 
 * #2 job is the boolean flag isConnected
 * 
 * One instance for each client connection. 
 * 
 * multithreaded access is possible. Therefore AtomicInteger is convenient though not necessary.
 *
 */
public class ClientSession implements Closeable {
	private AtomicInteger seqOut = new AtomicInteger(1);
	private AtomicInteger seqInExpected = new AtomicInteger(2);//logon ack skipped
	private boolean isConnected = true;

	public void setIsConnected(boolean b) {
		this.isConnected = b;
	}

	public boolean isConnected() {
		return isConnected;
	}
	public int incrementAndGetSeq() {
		int ret = this.seqOut.incrementAndGet();
		return ret;
	}
	public int getExpectedIncomingSeq() {
		return seqInExpected.get();
	}
	public void rollExpectedIncomingSeq() {
		seqInExpected.incrementAndGet();
	}
	@Override
	public void close(){
		// object should be garbaged collected soon
		seqOut = seqInExpected = null; // any accidental use after close would throw NPE
		setIsConnected(false);
	}	
}
