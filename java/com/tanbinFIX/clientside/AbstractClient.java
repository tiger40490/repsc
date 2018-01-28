//$Id$
package com.tanbinFIX.clientside;

import java.io.BufferedReader;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;

import com.tanbinFIX.bothside.OutStreamWrapper;
import com.tanbinFIX.bothside.format.FIXMsgField;
import com.tanbinFIX.bothside.format.FIXMsgParser;
import com.tanbinFIX.clientside.config.ConfigServiceFactory;
import com.tanbinFIX.clientside.config.IConfigService;
import com.tanbinFIX.clientside.config.ConfigServiceFactory.ConfigType;
import com.tanbinFIX.clientside.state.AbstractSate;
import com.tanbinFIX.clientside.state.LogonPending;
import com.tanbinFIX.clientside.state.LogoutPending;

/**
 * one instance represents one connection to the server.
 */
abstract public class AbstractClient implements Closeable {
	protected final int clientId;
	protected final Socket clientSocket;
	protected final IConfigService config;
	protected Destroyer heartBeatCheck;
	private HeartBeatSender heartBeatSender;
	protected final BufferedReader in;
	long lastHeartBeatOrAnythingReceived;
	protected final OutStreamWrapper out;
	protected final String serverHostName;
	protected ClientSession session;

	protected AbstractClient(int clientid, ConfigType configType) {
		clientId = clientid;
		config = ConfigServiceFactory.getConfigService(configType);
		serverHostName = config.getServerHostName();
		try {
			clientSocket = new Socket(serverHostName, 4444);
			out = new OutStreamWrapper(new PrintWriter(clientSocket.getOutputStream(), true));
			in = new BufferedReader(new InputStreamReader(clientSocket
					.getInputStream()));
		} catch (UnknownHostException e) {
			throw new FatalClientSideError(String.format(
				"host unknown: %s. Irrecoverable error.", serverHostName), e);
		} catch (IOException e) {
			throw new FatalClientSideError(
					String
							.format(
								"Couldn't get I/O for the connection to: %s. Irrecoverable error.",
								serverHostName), e);
		}

	}

	/**
	 * template method
	 */
	final protected void carryConversation() throws IOException {
		new LogonPending().send(out, 1, "sending logon");
		String fromServer = null;
		try {
			while ((fromServer = in.readLine()) != null) {
				this.lastHeartBeatOrAnythingReceived = System
						.currentTimeMillis();
				System.out.println("Server: " + fromServer);
				ArrayList<String> fieldArray = FIXMsgParser
						.quickParse(fromServer);
				if (foundBadMsgSeq(fieldArray)) {
					break;
				}
				String msgType = fieldArray.get(FIXMsgField.MsgType.tag);
				if ("A".equals(msgType)) {// logon ack
					this.session = new ClientSession();
					this.heartBeatCheck = new Destroyer(this);
					this.heartBeatCheck.scheduleCheck();
					// spawn new thread to send heartbeat
					this.heartBeatSender = new HeartBeatSender(config
							.getHeartBeatIntervalMills(), out, session);
					this.get1stStateAfterLogon().send(out,
						session.incrementAndGetSeq(), "sending NOS");
				}
				if ("5".equals(msgType)) {// logout ack
					// should interrupt heatbeat thread
					System.out
							.println("Msg_1782: logout ack received. Closing everything.");
					break;
				}
				int sleepMillsForTesting = config.getSleepMillsForTesting();
				if (sleepMillsForTesting > 0) {
					try {
						Thread.sleep(sleepMillsForTesting);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}

				if ("0".equals(msgType)) {
					// should handle heart beat somehow
				}
				handleOtherMessageTypes(fieldArray, msgType);
			}
		} catch (SocketException se) {
			if (!session.isConnected()) {
				System.err
						.println("Socket/session closed. One possible reason -- The checker thread probably detected " +
								"connection drop and closed the socket");
			} else {
				throw se;
			}
		}
	}

	/**
	 * release all resources
	 */
	@Override
	public void close() {
		if (session != null) {
			session.close();
		}
		if (heartBeatCheck != null) {
			heartBeatCheck.close();
		}
		if (heartBeatSender != null) {
			heartBeatSender.close();
		}
		out.close();
		try {
			in.close();
			clientSocket.close();
		} catch (IOException e) {
			// i don't think this error is a showstopper. Just log and proceed.
			e.printStackTrace();
		}
	}

	protected boolean foundBadMsgSeq(List<String> list) {
		int seqReceived;
		try {
			seqReceived = Integer.parseInt(list.get(FIXMsgField.MsgSeqNum.tag));
		} catch (NumberFormatException e) {
			throw new FatalClientSideError(
					"Serious system error. FIX server should never send a non-integer under tag 34.",
					e);
		}
		int firstMsgSeqExpectedFromServer = 1;
		int expectedIncomingSeq = (session == null) ? firstMsgSeqExpectedFromServer : session
				.getExpectedIncomingSeq();
		// System.out.printf("%s, %s\n", expectedIncomingSeq,seqReceived);
		if (seqReceived == expectedIncomingSeq) {
			// System.out.println("seq matched, we received exactly what we
			// expect. Next incoming msg must use a higher number");
			if (session != null) {
				session.rollExpectedIncomingSeq();
			}
			return false;
		} else if (seqReceived > expectedIncomingSeq) {
			System.out
					.println("Seq too high. We need to send Resend Request <2> message");
			return false;
		} else {
			String msg = "Seq too low. Should disconnect";
			System.out.println(msg);
			LogoutPending tmp = new LogoutPending();
			tmp.send(out, getSession().incrementAndGetSeq(), "sending logout (abnormal)");	
			return true;
		}
	}

	abstract protected AbstractSate get1stStateAfterLogon();

	public IConfigService getConfig() {
		return this.config;
	}

	public OutStreamWrapper getOutputStream() {
		return out;
	}

	public ClientSession getSession() {
		return session;
	}

	abstract protected void handleOtherMessageTypes(
			ArrayList<String> fieldArray, String msgType);

	public boolean isConnected() {
		return (session == null) ? false : session.isConnected();
	}
}
