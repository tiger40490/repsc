package com.nsdq.drone.devices;

/**
 * drone orientation as if on a photograph
 */
public class OrientationSensor implements ISnapshotSensor {
    double getPitch() {
    	return 0;//should query hardware
    }
    double getRoll() {
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
