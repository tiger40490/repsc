package com.nsdq.drone.devices; //v1

import com.nsdq.drone.Direction;
import com.nsdq.drone.SpeedTuple;

/**
 * based on the gyroscope 
 */
public class SelfMotionSensor implements IReadableDevice {
    SpeedTuple getX_Speed() {
    	return new SpeedTuple(0,0); //should query the hardware in real time	
    }
    SpeedTuple getY_Speed() {
    	return new SpeedTuple(0,0); //should query the hardware in real time	
    }
    SpeedTuple getZ_Speed() {
    	return new SpeedTuple(0,0); //should query the hardware in real time	
    }
    ///////// movement direction
    Direction getDirectionFromSpeed() {
    	return new Direction(getX_Speed().speed, getY_Speed().speed, getZ_Speed().speed);
    }
    /**
     * acceleration vs velocity directions can have any angle between them. 2 independent directions.
     */
    Direction getAcceleratingDirectionFromSpeed() {
    	return new Direction(getX_Speed().acceleration, 
    			getY_Speed().acceleration, getZ_Speed().acceleration);
    }
    
    ////////// spin motion of the drone (not spin of the gyroscope)
    Direction getSpinAxis() {
    	return new Direction(0,0,0); //should query the hardware in real time	
    }
    public SpeedTuple getSpinSpeedAroundAxis() { //should be below 1 revolution/second
    	return new SpeedTuple(0,0);  //should query the hardware in real time		
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
