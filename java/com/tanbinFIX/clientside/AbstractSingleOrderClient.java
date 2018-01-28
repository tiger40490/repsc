//$Id$
package com.tanbinFIX.clientside;

import java.io.IOException;

import com.tanbinFIX.clientside.config.ConfigServiceFactory.ConfigType;

abstract public class AbstractSingleOrderClient extends AbstractClient{
	protected AbstractSingleOrderClient(int clientid, ConfigType configType) {
		super(clientid, configType);
		
	}

	/**
	 * template method to ensure we always close().
	 * 
	 * Prevent resouce leaks
	 */
	public final void sendNewOrderSingle() throws IOException {
		try {
			this.carryConversation();
		} finally {
			this.close();
		}
	}
}
