package com.nsdq.drone.devices;

/**
 * @author Victor Tan
 * Position relative to ground antenna
 */
public class PositionSensor implements ISnapshotSensor {
	public double getX() {
    	return 0;//should query hardware		
	}
	public double getY() {
    	return 0;//should query hardware		
	}
	public double getZ() {
    	return 0;//should query hardware		
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
