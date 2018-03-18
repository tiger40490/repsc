package com.nsdq.drone.devices;

public class BladeEngine implements Readable {
	/**
	 * target power level is usually not same as current power level.
	 * 
	 * Look at air-conditioner for illustration.
	 */
	void setTargetPowerLevel(int level) {
        //should send a signal to hardware
	}
	int getCurrentPowerLevel() {
		return 0; //should query the hardware in real time		
	}
	/**
	 * "final" helps in-line
	 */
	final boolean isEngineOn() {
		return getCurrentPowerLevel() > 0;
	}
	/**
	 * Blade can have speed even when engine is off .. important sometimes
	 */
	int getBladeSpeed() {
		return 0; //should query the hardware blade controller in real time
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
