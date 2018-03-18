package com.nsdq.drone.devices;

import com.nsdq.drone.AbstractCommand;

public class CommandReceiver implements IReadableDevice {
	public AbstractCommand getIncomingCommand() {
		return null; //should query hardware
	}

	@Override
	public int getUniqueId() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public String getName() {
		// TODO Auto-generated method stub
		return null;
	}

}
