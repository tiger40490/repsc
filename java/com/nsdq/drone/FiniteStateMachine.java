package com.nsdq.drone; //v.9

import java.util.Date;

/**
 * simplified implementation of a state machine.
 * 
 * I would like to keep the responsibility of this class as samll as possible. so
 * it doesn't know any devices;
 * it doesn't know any direction, position or orientation.
 * it knows a specific target is reached only when Sofia informs it via markCompletion(). 
 * There's no point asking this state machine how far we are to a target -- query the sensors!
 */
public class FiniteStateMachine {
	private DeducedSystemState currentState=DeducedSystemState.Uninitialized;
	/**
	 * After we reach targetState, we stay in the target state
	 */
	private DeducedSystemState targetState=DeducedSystemState.Uninitialized;
	private Date takeOffCmdReceived = null;
	static private FiniteStateMachine instance = new FiniteStateMachine();
	private FiniteStateMachine() {	}
	static public FiniteStateMachine getInstance() {
		return instance;
	}
	
	/**
	 * Responsibility: set correct target but do not monitor progress -- Fire-and-Forget
	 * 
	 * Follow-up would create tight coupling between this and device classes, 
	 * but this class doesn't know the devices.
	 */
	public void handleCommand_TakeOff() {
		setTargetState(DeducedSystemState.Drifting);
		takeOffCmdReceived = new Date(); //overwrite the null!
	}
	public void handleCommand_moveUp() {
		setTargetState(DeducedSystemState.Enroute);
	}	
	public void handleCommand_stablize() {
		setTargetState(DeducedSystemState.Hovering);
	}
	public void handleCommand_land() {
		setTargetState(DeducedSystemState.Landed);
	}

	public boolean isTakeoffTakingTooLong() {
		return (targetState == DeducedSystemState.Drifting) &&
				(new Date().getTime() - takeOffCmdReceived.getTime()> 1000*10); 
	}
	/***
	 * Only Sofia can determine if we have reached our target. Sofia will call this method.
	 */
	public void markCompletion() {
		this.setCurrentState(getTargetState());
	}
	public DeducedSystemState getTargetState() {
		if (targetState == null) throw new IllegalStateException("should never be null");
		return targetState;
	}
	public void setTargetState(DeducedSystemState targetState) {
		if (targetState == null) throw new IllegalArgumentException("programmer error passing null DroneState");
		this.targetState = targetState;
		takeOffCmdReceived = null;
	}
	public DeducedSystemState getCurrentState() {
		if (currentState == null) throw new IllegalStateException("should never be null");
		return currentState;
	}
	public void setCurrentState(DeducedSystemState newState) {
		if (newState == null) throw new IllegalArgumentException("programmer error passing null DroneState");
		this.currentState = newState;
	}
}
