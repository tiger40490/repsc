/**
 * 
 */
package com.nsdq.drone.devices;

/**
 * Any device that we can read from
 */
public interface IReadableDevice {
	int getUniqueId();
	
	/**
	 * Not necessarily unique, used for display
	 */
	String getName(); 
}
