package com.nsdq.drone;

/**
 * a value of 1,1,1 would mean a direction 45 degrees up, 45 degrees between north and east 
 */
public final class Direction {
	static public final Direction NO_MOVE=new Direction(0,0,0)
;	final double north, east, up;
	
	/**
	 * {1,1,1} is same as {2,2,2} direction
	 */
	public Direction(double x,double y,double z) {
		final double length = Math.sqrt(x*x + y*y +z*z);
		north = x/length;
		east = y/length;
		up = z/length;
	}
}
