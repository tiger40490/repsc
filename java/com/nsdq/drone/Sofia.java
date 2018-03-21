package com.nsdq.drone; //v0.8

import java.util.*;
import java.util.concurrent.LinkedBlockingQueue;

import com.nsdq.drone.devices.BladeEngine;
import com.nsdq.drone.devices.CommandReceiver;
import com.nsdq.drone.devices.MotionSensor;
import com.nsdq.drone.devices.OrientationSensor;
import com.nsdq.drone.devices.PositionSensor;
import com.nsdq.drone.devices.TapSensor;

class ShowStatus extends Cmd{
	@Override
	public void execute(FiniteStateMachine fsm) {
		System.out.println(fsm.getCurrentState());
	}
}
class TakeOff extends Cmd{
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_TakeOff();
	}	
}
class Stablize extends Cmd{
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_stablize();
	}	
}
class TouchDown extends Cmd{
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_land();
	}	
}
class ReturnHome extends Cmd{
	@Override
	boolean shouldExit() { return true;}
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_land();		
	}	
}
class MoveUp extends Cmd{
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_moveUp();
	}	
}
class MoveUpDistance extends Cmd{
	private double distance;
	MoveUpDistance(double d){
		this.distance = d;
	}
	@Override
	public void execute(FiniteStateMachine fsm) {
		fsm.handleCommand_moveUp();
	}
	@Override
	double getNumericValue() {
		return distance;
	}
}
public class Sofia {
	public static final Cmd EMPTY_CMD=new EmptyCommand();
	
	/**
	 * this queue always has 1 or 2 elements. If no real command, then we should put in the EMPTY_CMD
	 */
	private Queue<Cmd> acceptedCommands=new LinkedBlockingQueue<>(2); //at most 2 commands including current
	
	private final FiniteStateMachine fsm=FiniteStateMachine.getInstance();
	private Direction targetDirection = Direction.MOTIONLESS;
	private double targetValue;
	private Map<Date, Cmd> commandsCompleted = new TreeMap<>(); //history
	
	//on-board devices:
	private BladeEngine[] engines = {new BladeEngine("front-left"), new BladeEngine("front-right"), 
			new BladeEngine("back-left"), new BladeEngine("back-right")};
	private MotionSensor motionSensor = new MotionSensor();
	private OrientationSensor orSensor = new OrientationSensor();
	private PositionSensor posSensor = new PositionSensor();
	private TapSensor tapSensor = new TapSensor();
	private CommandReceiver cmdReceiver = new CommandReceiver();
	
	enum SensorAnalysisResult{	InProgress/*towards target*/, TargetReached, Distress;	} 
	
	Sofia(){
		this.acceptedCommands.add(EMPTY_CMD);
	}
	/**
	 * Break the loop by sending a ExitLoop command 
	 */
	void mainLoop() throws InterruptedException {
		for(;;Thread.sleep(1)) {
			//Top priority:
			SensorAnalysisResult status=checkSensors();
			//priority 2:
			if (fsm.isTakeoffTakingTooLong()) {
				System.err.println("Take-off has taken more than 10 seconds");
				status =SensorAnalysisResult.Distress;
			}
			//Priority 3:
			if (status==SensorAnalysisResult.Distress) {
				System.err.println("Distress...");
				fsm.setCurrentState(DeducedSystemState.Lost);
				fsm.setTargetState(DeducedSystemState.Landed);
				this.acceptedCommands.clear(); //abandon all commands
				this.acceptedCommands.add(new TouchDown()); //touch down immediately
			}
			//priority 4:
			if (fsm.getCurrentState() == DeducedSystemState.Lost && tapSensor.wasTappedWithinX_second(1)) {
				this.reInitialize();
			}
			//priority 5: check command completion
			if (status == SensorAnalysisResult.TargetReached) {
				commandsCompleted.put(new Date(), acceptedCommands.poll());
				if (acceptedCommands.isEmpty()) acceptedCommands.add(EMPTY_CMD);/*avoid empty queue*/
				fsm.markCompletion();
				//Priority 6: 
				this.acceptIncomingCommand();
			}
			if (isCmdEmpty()) continue;
			if (acceptedCommands.peek().shouldExit()) break;			
			//Special logic for MoveUp or MoveDistance(3):
			Direction tmp = acceptedCommands.peek().getTargetDirection();
			if (tmp != Direction.MOTIONLESS)
				this.targetDirection  = tmp;
			
			double tmp2 = acceptedCommands.peek().getNumericValue();
			if (tmp2>0)
				this.targetValue  = tmp2;
			
			execute(acceptedCommands.peek()); //do not remove from queue
		}
		
		//special logic for ReturnHome command:
		assert acceptedCommands instanceof ReturnHome;
		assert fsm.getTargetState() == DeducedSystemState.Landed;
		for(;;Thread.sleep(1)) { //Wait until we are landed
			if (checkSensors() == SensorAnalysisResult.TargetReached) break; //Landed 
		}
	}
	/**Principle -- reacting to sensors is higher priority over processing new commands. 
	 * 
	 * Command can wait for some microseconds. If sensors indicate drone is off course or over-spinning
	 * we need to correct it ASAP or risk crashing. 
	 */
	private SensorAnalysisResult checkSensors() {
		for (BladeEngine engine: engines) {
		  if (engine.getTemperature() > 100) return SensorAnalysisResult.Distress;
		  if (!engine.isEngineOn() && fsm.getCurrentState() != DeducedSystemState.Landed)
			 return SensorAnalysisResult.Distress;
		}
		if (motionSensor.getSpinSpeedAroundAxis().speed > 1) {
			 return SensorAnalysisResult.Distress;//too much spinning, likely out of control
		}
		//process other sensors
		// 
		// if target reached, then return SensorAnalysisResult.TargetReached.
		// There will lots of calculation to determine whether target is reached.
		//
		// if in progress, then calculate what signals to send to the 4 engines
		return SensorAnalysisResult.InProgress;
	}
	boolean isCmdEmpty() {
		return acceptedCommands.isEmpty() ||acceptedCommands.peek() == EMPTY_CMD;
	}
	private void acceptIncomingCommand() {
		if (!isCmdEmpty()) return; //current command not completed
		Cmd tmp = cmdReceiver.getIncomingCommand();
		if (tmp != EMPTY_CMD) {
			this.acceptedCommands.clear(); 
			if (tmp.getClass() == TouchDown.class) {
				this.acceptedCommands.add(new Stablize());/* Put two commands into the queue
First the drone must reach the Hovering state. At that time first command would be removed 
from queue. Then the 2nd command (Land) would execute.*/
			}
			this.acceptedCommands.add(tmp);		
		}
	}
	private void execute(Cmd cmd) {
		cmd.execute(fsm);
	}
	private void reInitialize() {}//initialize all devices and hope to regain control
}