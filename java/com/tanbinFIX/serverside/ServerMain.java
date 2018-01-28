//$Id$
package com.tanbinFIX.serverside;

import java.io.IOException;

import com.tanbinFIX.bothside.MyUtil;

public class ServerMain {
	public static final int HOW_MANY_TESTS = 3;
	static ConnectionManager cm = new ConnectionManager();

	public static void main(String[] args) throws IOException {
		System.out
				.printf(
					"Server is waiting for connections. You can start "
							+ "the test client %s times. After that, this server will exit.\n",
					HOW_MANY_TESTS);

		for (int i = 0; i < HOW_MANY_TESTS; i++) {
			handleOneClient(new ClientProxy(cm.accept()));
		}
		cm.close();
	}

	private static void handleOneClient(ClientProxy p) throws IOException {
		if (p == null)
			return;
		String inputLine, outputLine;
		KnockKnockProtocol kkp = new KnockKnockProtocol();
		while ((inputLine = p.in.readLine()) != null) {
			outputLine = kkp.processInput(inputLine);
			if (MyUtil.hasText(outputLine)) {
				p.out.println(outputLine);
			}
		}
		p.close();
	}
}
