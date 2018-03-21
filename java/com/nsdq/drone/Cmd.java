package com.nsdq.drone; //v0.9

/**All command names should start with verbs.
 * 
 * Method should probably be public.
 *
 */
public abstract class Cmd{
	abstract void execute(FiniteStateMachine fsm); //no default implementation!
	
	/**Some commands demand an exit, but most commands don't.
	 */
	boolean shouldExit() { return false;}
	
	/**
	 * some commands come with a numeric value. If multiple values needed, then use some hashmap
	 */
	double getNumericValue() {
		return 0;
	}
	Direction getTargetDirection() {
		return Direction.MOTIONLESS;
	}
}

final class EmptyCommand extends Cmd{ //This class is instantiated only once to create a singleton constant
	@Override
	public void execute(FiniteStateMachine fsm) {}
}
