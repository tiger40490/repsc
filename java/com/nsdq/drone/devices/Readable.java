/**
 * 
 */
package com.nsdq.drone.devices;

/**
 */
public interface Readable {
	int getUniqueId();
	
	/**
	 * Not necessarily unique, used for display
	 */
	String getName(); 
}
