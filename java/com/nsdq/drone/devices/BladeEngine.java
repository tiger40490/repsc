package com.nsdq.drone.devices; //v1

public class BladeEngine implements IReadableDevice {
	private String _name="";
	public BladeEngine(String name) {
		assert name!=null && !name.isEmpty();
		this._name = name;
	}
	/**
	 * target power level is usually not same as current power level.
	 * 
	 * Look at air-conditioner for illustration.
	 */
	void setTargetPowerLevel(int level) {
        //should send a signal to hardware
	}
	public int getCurrentPowerLevel() {
		return 99; //should query the hardware in real time		
	}
	/**
	 * "final" helps in-line
	 */
	public final boolean isEngineOn() {
		return getCurrentPowerLevel() > 0;
	}
	/**
	 * Blade can have speed even when engine is off .. important sometimes
	 */
	public double getBladeSpeed() {
		return 0; //should query the hardware blade controller in real time
	}
	public double getTemperature() {
		return 0; //should query the hardware in real time	
	}
	@Override
	public int getUniqueId() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public String getName() {
		return this._name;
	}
}
