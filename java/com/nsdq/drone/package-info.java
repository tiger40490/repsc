/**
 * See also javadoc in FiniteStateMachine.java, DeducedSystemState, TapSensor.java, ISnapshotSensor.java
 * 
 * Sofia is the name of the runtime process on-board the drone.
 * 
 * <h1>====external interface====</h1>
 * 
 * <h2>--output--</h2>
 * Any time, drone state is available for query. State variables include things like
 * * absolute position relative to a ground antenna 
 * * movement
 * 
 * The other output is distress signal via STDERR/STDOUT.
 
 * <h2>--input: sensors--</h2>
 * Getters for every sensor is a simple input interface. Periodically, a polling loop would check all sensors.
 
 * We could adopt some multi-threaded design and use asynchronous event callback, but it raises interesting 
 * questions like
 
 * Q: when the done is reacting to an emergency event, does it ignore new asynchronous events?
 * Q: since the asynchronous events are probably not executed immediately, they must be saved 
 * in a buffer or queue which invites the classic conflation challenge -- earlier events are 
 * superseded by later events.
  
 * <h2>--input: commands--</h2>
 * Commands are sent from RemoteControl instance.
 * 
 * These inputs are rather infrequent compared to sensor inputs. I will use polling to read commands. 
 * When Sofia is still executing one command, it can't really accept another command. The only exception 
 * is the TouchDown command, which inserts an additional Stablize command at front of the task queue.
 * 
 * To avoid confusing, I renamed the Land command to TouchDown.

 * I implemented MoveUp but the other 5 Move* are no different.
 * 
 * As a bonus, I made provisions for composite commands like
 * MoveUp2MetersLeft3Meters = MoveUp -> MoveDistance(3) -> MoveLeft -> MoveDistance(3) Please 
 * see javadoc in MoveDistance class
 * 
 * <h1>====internal interface====</h1>
 * Each command will drive a loop until target-state is reached. 
 * During the looping, if engine is found to be off (discovered via polling), target-state would 
 * change to something like LANDED.
 * 
 * Sofia gets closer to a target-state by sending internal requests to the engines. 
 * All other Sofia components are read-only sensors.
 * 
 * <h2>--target states--</h2>
 * target state LANDED == { no movement in drone or the blade; engine is effectively off (perhaps in Neutral gear)}
 * By the laws of physics, altitude has to be zero.
 * 
 * target state HOVERING == {no movement except possible spin; blade speed > 0; engine power level > minimum}
 * 
 * These and other states are not implemented in Sofia.checkSensors() method.
 * 
 * <h2>--algorithms:--</h2>
 * For each Command, in each loop iteration, Sofia makes incremental decisions about what specific signals to send 
 * the four engines. Sofia makes these decisions based on polling sensor results, following some algorithm.  
 * These algorithms are not implemented in Sofia.checkSensors() method. 
 */
package com.nsdq.drone;






















