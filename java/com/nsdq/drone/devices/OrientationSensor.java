package com.nsdq.drone.devices; //v1

/**
 * drone orientation as if on a photograph
 */
public class OrientationSensor implements ISnapshotSensor {
    double getPitch() {
    	return 0;//should query the hardware in real time	
    }
    double getRoll() {
    	return 0;//should query the hardware in real time	
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
