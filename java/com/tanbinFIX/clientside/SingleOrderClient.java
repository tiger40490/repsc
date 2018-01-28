//$Id$
package com.tanbinFIX.clientside;

import java.util.ArrayList;

import com.tanbinFIX.clientside.config.ConfigServiceFactory;
import com.tanbinFIX.clientside.state.LogoutPending;
import com.tanbinFIX.clientside.state.NewOrderPending;

/**
 * 
 */
public class SingleOrderClient extends AbstractSingleOrderClient {
	public SingleOrderClient(int clientId, ConfigServiceFactory.ConfigType configType) {
		super(clientId, configType);
	}

	@Override
	protected void handleOtherMessageTypes(ArrayList<String> fieldArrayForFutureUse, String msgType) {
		if ("8".equals(msgType)) { // order ack
			new LogoutPending().send(out, session.incrementAndGetSeq(), "sending NOS");
		}
	}

	@Override
	protected NewOrderPending get1stStateAfterLogon() {
		return new NewOrderPending();
	}
}