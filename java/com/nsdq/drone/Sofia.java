/**
 * 
 */
package com.nsdq.drone;

import com.nsdq.drone.devices.BladeEngine;
import com.nsdq.drone.devices.MotionSensor;
import com.nsdq.drone.devices.OrientationSensor;
import com.nsdq.drone.devices.PositionSensor;

/**
 * @author Victor Tan
 *
 */
abstract class AbstractCommand{
	abstract void execute(FiniteStateMachine fsm);
	double getValue() {
		return 0;
	}
	Direction getDirection() {
		return Direction.NO_MOVE;
	}
}
final class EmptyCommand extends AbstractCommand{
	@Override
	public void execute(FiniteStateMachine fsm) {}
}
class TakeOff extends AbstractCommand{
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_TakeOff();
	}	
}
class Stablize extends AbstractCommand{
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_stablize();
	}	
}
class Land extends AbstractCommand{
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_land();
	}	
}
class MoveUp extends AbstractCommand{
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_moveUp();
	}	
}
/**
 * We can create composite commands line 
 * @author Victor Tan
 *
 */
class MoveDistance extends AbstractCommand{
	private double distance;
	MoveDistance(double d){
		this.distance = d;
	}
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_moveUp();
	}
	@Override
	double getValue() {
		return distance;
	}
}
public class Sofia {
	private static final AbstractCommand EMPTY_COMMAND = new EmptyCommand();
	private AbstractCommand nonNullCommand=EMPTY_COMMAND;
	private final FiniteStateMachine fsm=FiniteStateMachine.getInstance();
	
	//on-board devices:
	private BladeEngine[] engines = {new BladeEngine("front-left"), new BladeEngine("front-right"), 
			new BladeEngine("back-left"), new BladeEngine("back-right")};
	private MotionSensor motionSensor = new MotionSensor();
	private OrientationSensor orSensor = new OrientationSensor();
	private PositionSensor posSensor = new PositionSensor();
	private Direction targetDirection_nonNull = Direction.NO_MOVE;
	
	/**
	 * 
	 * @throws InterruptedException
	 */
	void mainLoop() throws InterruptedException {
		for(;;Thread.sleep(1)) {
			//TODO: if command is exit then break
			if (checkSensors()) {
				System.err.println("Distress...");
				fsm.setCurrentState(DroneState.Lost);
			}
			if (checkProgress()) {
				fsm.markCompletion();
			}
			if (!hasNewCommand()) continue;
			execute(nonNullCommand);
			for (Direction tmp = nonNullCommand.getDirection();;)
				this.targetDirection_nonNull  = tmp;
			
		}
		
	}
	/**
	 * checks all sensors to decide how far we are to target
	 * @return true to indicate target reahed
	 */
	private boolean checkProgress() {
		return false;
	}
	/**Principle -- reacting to sensors is higher priority over processing new commands. 
	 * 
	 * Command can wait for some microseconds. If sensors indicate drone is off course or over-spinning
	 * we need to correct it ASAP or risk crashing.
	 * 
	 * @return false if malfunction detected.
	 */
	private boolean checkSensors() {
		//process all sensor
		if (fsm.getCurrentState() != fsm.getTargetState()) {
			
		}
		return true;
	}
	private void execute(AbstractCommand cmd) {
		cmd.execute(fsm);
		this.nonNullCommand = EMPTY_COMMAND;
	}
	private boolean hasNewCommand() {
		return nonNullCommand != EMPTY_COMMAND;
	}
}
