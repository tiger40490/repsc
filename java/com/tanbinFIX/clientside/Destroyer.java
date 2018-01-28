//$Id$
package com.tanbinFIX.clientside;

import java.io.Closeable;
import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

import com.tanbinFIX.clientside.config.IConfigService;
import com.tanbinFIX.clientside.state.LogoutPending;

/**
 * a schedule task to kick in at the right time to check the "silence" period
 * since the last msg received on a given socket. If silence exceeds a threshold
 * (60 sec?), send a logout msg to the socket and close the socket. This would
 * unblock the main loop.
 * 
 * There is tight coupling between this object and the Client object and the
 * session object, to be improved.
 * 
 */
public class Destroyer implements Callable<Void>, Closeable {
	final private AbstractClient clientConnection;
	private final IConfigService config;
	/**
	 * failure/death/termination in the thread is handled better than in
	 * Timer.java
	 */
	final private ScheduledExecutorService faultTolerantThreadPool;
	/**
	 * There should be just one task in the queue, thanks to
	 */
	private ScheduledFuture<Void> theScheduledTask;
	final private long silenceThreshold;

	public Destroyer(AbstractClient abstractClient) {
		assert abstractClient != null;
		this.clientConnection = abstractClient;
		faultTolerantThreadPool = Executors.newSingleThreadScheduledExecutor();
		config = clientConnection.getConfig();
		silenceThreshold = config.getSilenceThreshold();
	}

	@Override
	public Void call() {
		System.out.println("checking connection liveness...");
		if (!clientConnection.isConnected()) {
			return null;
		} else if (System.currentTimeMillis()
				- clientConnection.lastHeartBeatOrAnythingReceived > silenceThreshold) {
			new LogoutPending().send(clientConnection.out, clientConnection
					.getSession().incrementAndGetSeq(),
				"sending logout (abnormal)");
			System.err
					.println("no heart beat (or any incoming msg) received for too long. "
							+ "Final logout msg successfully sent to server. "
							+ "Closing socket...");
			clientConnection.close();// force other socket users to exit
			return null;
		} else { // schedule the next check
			Destroyer checker = new Destroyer(clientConnection);
			this.theScheduledTask = faultTolerantThreadPool.schedule(checker,
				config.getCheckInterval(), TimeUnit.MILLISECONDS);

		}
		return null;
	}

	public void scheduleCheck() {
		this.faultTolerantThreadPool.schedule(this, config.getCheckInterval(),
			TimeUnit.MILLISECONDS);
	}

	@Override
	public void close() {
		if (theScheduledTask != null) {
			this.theScheduledTask.cancel(true);
		}
		if (faultTolerantThreadPool != null) {
			this.faultTolerantThreadPool.shutdownNow();
		}
	}
}
