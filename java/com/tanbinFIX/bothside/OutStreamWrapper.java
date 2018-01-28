//$Id$
package com.tanbinFIX.bothside;

import java.io.Closeable;
import java.io.PrintWriter;

/**
 * easier logging. Should be removed in production to avoid overhead of extra layering over PrintWriter.println()
 */
public class OutStreamWrapper implements Closeable {
	final private PrintWriter pw;

	public OutStreamWrapper(PrintWriter tmp) {
		this.pw = tmp;
	}

	public void println(String toServer, String labelForLogging) {
		if (MyUtil.hasText(labelForLogging))
			System.out.println("\t" + labelForLogging);
		System.out.println("Client: " + toServer);
		pw.println(toServer);
	}

	public void close() {
		pw.close();
	}
}
