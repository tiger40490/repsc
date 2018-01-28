//$Id$
package com.tanbinFIX.clientside;

import java.net.UnknownHostException;

public class FatalClientSideError extends RuntimeException {
	public FatalClientSideError(String msg, Throwable e) {
		super(msg, e);
	}

	public FatalClientSideError(String msg) {
		super(msg);
	}

//	@Override
//	public String getMessage() {
//		getCause();
//		return msg;
//	}
}
