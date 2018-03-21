package com.nsdq.drone.devices; //v1

import java.util.Date;

/**
 * Ignore any tap if drone is Not in distress.
 * 
 * Ignore any tap long ago.
 */
public class TapSensor implements IReadableDevice {
	private Date getLastTapTime() {
		return null; //query the hardware in real time		
	}
	public boolean wasTappedWithinX_second(int i) {
		return new Date().getTime() - getLastTapTime().getTime() < 1000 * i;
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
