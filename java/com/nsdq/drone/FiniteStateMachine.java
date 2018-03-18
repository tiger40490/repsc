package com.nsdq.drone;

/**
 * non-standard, simplified implementation of a state machine.
 * 
 * I would like to keep the responsibility of this class simple. so
 * it doesn't know any devices;
 * it doesn't know any direction or position
 *
 */
public class FiniteStateMachine {
	private DroneState currentState_nonNull=DroneState.Landed;
	/**
	 * After we reach targetState, we stay in the target state
	 */
	private DroneState targetState_nonNull=DroneState.Landed;
	static private FiniteStateMachine instance = new FiniteStateMachine();
	private FiniteStateMachine() {}
	static public FiniteStateMachine getInstance() {
		return instance;
	}
	
	/**
	 * Responsibility: set correct target but do not monitor progress -- Fire-and-Forget
	 * 
	 * Follow-up would create tight coupling between this and device classes!
	 */
	public void handleCommand_moveUp() {
		setTargetState(DroneState.Enroute);
	}	
	public void handleCommand_TakeOff() {
		setTargetState(DroneState.Drifting);
	}
	public void handleCommand_stablize() {
		setTargetState(DroneState.Hovering);
	}
	public void handleCommand_land() {
		setTargetState(DroneState.Landed);
	}
	/***
	 * Only Sofia can determine if we have reached our target. Sofia will call this method.
	 */
	public void markCompletion() {
		this.setCurrentState(getTargetState());
	}
	public final boolean hasNewTarget() {
		return getCurrentState() != getTargetState();
	}
	public DroneState getTargetState() {
		if (targetState_nonNull == null) throw new IllegalStateException("should never be null");
		return targetState_nonNull;
	}
	public void setTargetState(DroneState targetState) {
		if (targetState == null) throw new IllegalArgumentException("programmer error passing null DroneState");
		this.targetState_nonNull = targetState;
	}
	public DroneState getCurrentState() {
		if (currentState_nonNull == null) throw new IllegalStateException("should never be null");
		return currentState_nonNull;
	}
	public void setCurrentState(DroneState newState) {
		if (newState == null) throw new IllegalArgumentException("programmer error passing null DroneState");
		this.currentState_nonNull = newState;
	}
}
