package com.nsdq.drone;

/**
 * At any time, the drone is in exactly one of the states, but it may have zero or 1 target-state
 * 
 * If we don't query the sensors, we assume the state has not changed.
 * 
 * I don't like an UNKNOWN state.
 *
 */
public enum DroneState {
	Landed,
	Hovering,
	Enroute,
	
	/**
	 * A drone in distress could be moving to wards a target-state by momentum, but Sofia basically lost control
	 * and some of the sensors could be unreliable.
	 */
	Lost,
	
	/**
	 * In motion, under control, but without a new target-state. Sofia is in this state after take_off before 
	 * getting another commands
	 */
	Drifting,
}
