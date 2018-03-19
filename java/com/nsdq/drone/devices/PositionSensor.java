package com.nsdq.drone.devices; //v1

/**
 * Position relative to ground antenna
 */
public class PositionSensor implements ISnapshotSensor {
	public double getX() {
    	return 0;//should query the hardware in real time		
	}
	public double getY() {
    	return 0;//should query the hardware in real time		
	}
	public double getZ() {
    	return 0;//should query the hardware in real time		
	}

	@Override
	public int getUniqueId() {
		return 0;
	}

	@Override
	public String getName() {
		// TODO Auto-generated method stub
		return null;
	}

}
