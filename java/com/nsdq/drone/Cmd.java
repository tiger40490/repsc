package com.nsdq.drone; //v.9

public abstract class Cmd{
	abstract void execute(FiniteStateMachine fsm);
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

final class EmptyCommand extends Cmd{
	@Override
	public void execute(FiniteStateMachine fsm) {}
}
