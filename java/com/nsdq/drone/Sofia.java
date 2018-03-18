/**
 * 
 */
package com.nsdq.drone;

import java.util.*;

import com.nsdq.drone.devices.BladeEngine;
import com.nsdq.drone.devices.CommandReceiver;
import com.nsdq.drone.devices.MotionSensor;
import com.nsdq.drone.devices.OrientationSensor;
import com.nsdq.drone.devices.PositionSensor;

/**
 * @author Victor Tan
 *
 */
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
class ExitLoop extends AbstractCommand{
	@Override
	boolean shouldExit() { return true;}
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
/**Bonus feature not specified in original requirements
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
	public static final AbstractCommand EMPTY_CMD=new EmptyCommand();
	private AbstractCommand acceptedCommand=EMPTY_CMD;
	private final FiniteStateMachine fsm=FiniteStateMachine.getInstance();
	private Direction targetDirection_nonNull = Direction.MOTIONLESS;
	private double targetValue;
	private Map<Date, AbstractCommand> commandsCompleted = new TreeMap<>();
	
	//on-board devices:
	private BladeEngine[] engines = {new BladeEngine("front-left"), new BladeEngine("front-right"), 
			new BladeEngine("back-left"), new BladeEngine("back-right")};
	private MotionSensor motionSensor = new MotionSensor();
	private OrientationSensor orSensor = new OrientationSensor();
	private PositionSensor posSensor = new PositionSensor();
	private CommandReceiver cmdReceiver = new CommandReceiver();
	
	enum SensorAnalysisResult{InProgress, TargetReached, Distress} 
	/**
	 * Break the loop by sending a kill signal
	 */
	void mainLoop() throws InterruptedException {
		for(;;Thread.sleep(1)) {
			SensorAnalysisResult status=checkSensors();
			if (status==SensorAnalysisResult.Distress) {
				System.err.println("Distress...");
				fsm.setCurrentState(DroneState.Lost);
			}
			if (status == SensorAnalysisResult.TargetReached) {
				commandsCompleted.put(new Date(), acceptedCommand);
				this.acceptedCommand = EMPTY_CMD;
				fsm.markCompletion();
			}
			this.checkIncomingCommand();
			if (isCmdEmpty()) continue;
			if (acceptedCommand.shouldExit()) break;
			execute(acceptedCommand);
			Direction tmp = acceptedCommand.getTargetDirection();
			if (tmp != Direction.MOTIONLESS)
				this.targetDirection_nonNull  = tmp;
			
			double tmp2 = acceptedCommand.getValue();
			if (tmp2>0)
				this.targetValue  = tmp2;
		}
		assert acceptedCommand instanceof ExitLoop;
		assert fsm.getTargetState() == DroneState.Landed;
		for(;;Thread.sleep(1)) {
			//SensorAnalysisResult 
			if (checkSensors() == SensorAnalysisResult.TargetReached) break; //Landed 
		}
	}
	/**Principle -- reacting to sensors is higher priority over processing new commands. 
	 * 
	 * Command can wait for some microseconds. If sensors indicate drone is off course or over-spinning
	 * we need to correct it ASAP or risk crashing.
	 * 
	 * @return false (bad) if malfunction detected.
	 */
	private SensorAnalysisResult checkSensors() {
		//process all sensor
		// if in distress, then return SensorAnalysisResult.Distress
		// 
		// if target reached, then return SensorAnalysisResult.TargetReached
		//
		// if in progress, then issue signals to the 4 engines based on the sensors
		return SensorAnalysisResult.InProgress;
	}
	boolean isCmdEmpty() {
		return this.acceptedCommand == EMPTY_CMD;
	}
	private void checkIncomingCommand() {
		if (!isCmdEmpty()) return; //current command not completed
		AbstractCommand tmp = cmdReceiver.getIncomingCommand();
		if (tmp != EMPTY_CMD)
			this.acceptedCommand = tmp;		
	}
	private void execute(AbstractCommand cmd) {
		cmd.execute(fsm);
	}
}
