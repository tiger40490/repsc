package com.nsdq.drone.devices;

import com.nsdq.drone.Direction;
import com.nsdq.drone.Motion;

/**
 * based on the gyroscope 
 */
public class SpeedSensor implements Readable {
    Motion getX_Speed() {
    	return new Motion(0,0); //should query hardware
    }
    Motion getY_Speed() {
    	return new Motion(0,0); //should query hardware
    }
    Motion getZ_Speed() {
    	return new Motion(0,0); //should query hardware
    }
    ///////// movement direction
    Direction getDirectionFromSpeed() {
    	return new Direction(getX_Speed().speed, getY_Speed().speed, getZ_Speed().speed);
    }
    /**
     * acceleration vs velocity directions can have any angle between them. 2 independent directions.
     */
    Direction getAcceleratingDirectionFromSpeed() {
    	return new Direction(getX_Speed().acceleration, getY_Speed().acceleration, getZ_Speed().acceleration);
    }
    
    ////////// spin motion
    Direction getSpinAxis() {
		// TODO Auto-generated method stub
    	return new Direction(0,0,0); //should query hardware
    }
    Motion getSpinSpeedAroundAxis() {
		// TODO Auto-generated method stub
    	return new Motion(0,0); //should query hardware
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
