package com.nsdq.drone; //v1

/**
 * At any time, the system is in exactly one of the states listed here, but it may have zero or 1 target-state
 * 
 * If we don't query the sensors, we assume the state has not changed.
 * 
 * Warning: actual physical state of the drone is often unknown, like in a storm, or caught in trees
 * The states here are deduced from the last sensor readings. Therefore, these are delayed estimates 
 * at best. It would be dangerous to trust these conclusions 100%!
 * 
 * Remember, the system (named Sofia) is a running process whereas the drone is a real flying machine. 
 * They are two different things. Normally, Sofia knows the precise condition of the machine and 
 * can send it signals via the BladeEngine interface.
 */
public enum DeducedSystemState {
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
	Uninitialized,
}
