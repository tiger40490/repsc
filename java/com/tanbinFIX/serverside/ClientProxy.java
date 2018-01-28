//$Id$
package com.tanbinFIX.serverside;

import java.io.BufferedReader;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * represents a connection from a client. Therefore This is a kind of "proxy"
 * that stands in for a client.
 * 
 */
public class ClientProxy implements Closeable {
	public final PrintWriter out;
	public final BufferedReader in;
	public final Socket clientSocket;

	public ClientProxy(Socket _clientSocket) throws IOException {
		this.clientSocket = _clientSocket;
		out = new PrintWriter(clientSocket.getOutputStream(), true);
		in = new BufferedReader(new InputStreamReader(clientSocket
				.getInputStream()));
	}

	@Override
	public void close() {
		out.close();
		try {
			in.close();
			clientSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
