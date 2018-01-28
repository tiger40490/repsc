//$Id$
package com.tanbinFIX.clientside;

import java.io.IOException;

import com.tanbinFIX.clientside.config.ConfigServiceFactory.ConfigType;

public class ClientMain {
	public static void main(String[] args) throws IOException {
		int fakeClientId = 123;
		AbstractSingleOrderClient sw = new SingleOrderClient(fakeClientId, ConfigType.TEST);
		sw.sendNewOrderSingle();
	}
}
