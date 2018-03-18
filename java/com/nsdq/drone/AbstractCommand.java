package com.nsdq.drone;

public abstract class AbstractCommand{
	abstract void execute(FiniteStateMachine fsm);
	boolean shouldExit() { return false;}
	double getValue() {
		return 0;
	}
	Direction getTargetDirection() {
		return Direction.MOTIONLESS;
	}
}

final class EmptyCommand extends AbstractCommand{
	@Override
	public void execute(FiniteStateMachine fsm) {}
}
