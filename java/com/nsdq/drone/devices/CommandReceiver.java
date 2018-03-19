package com.nsdq.drone.devices; //v1

import com.nsdq.drone.Cmd;

public class CommandReceiver implements IReadableDevice {
	public Cmd getIncomingCommand() {
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
