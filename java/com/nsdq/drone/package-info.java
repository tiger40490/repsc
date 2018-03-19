/**
 * See also javadoc in FiniteStateMachine.java, TapSensor.java, ISnapshotSensor.java
 * 
 * Sofia is the name of the runtime process on-board the drone.
 * 
 * <h1>====external interface====</h1>
 * 
 * <h2>--output--</h2>
 * Any time, drone state is available for query. State variables include:
 * * absolute position relative to a ground antenna 
 * * movement
 * * engine on/off
 * 
 * The other output is distress signal via STDOUT. I won't go any deeper on this part.
 
 * <h2>--input: sensors--</h2>
 * Getters for every sensor is a simple input interface. Periodically, a polling thread would check the sensors.
 
 * We could adopt some multi-threaded design and use asynchronous event callback, but it raises interesting questions like
 
 * Q: when the done is reacting to an emergency event, does it ignore new asynchronous events?
 * Q: since the asynchronous events are probably not executed immediately, they must be saved 
 * in a buffer or queue which invites the classic conflation challenge -- earlier events are 
 * superseded by later events.
  
 * <h2>--input: commands--</h2>
 * Commands are sent from RemoteControl instance.
 * 
 * These inputs are infrequent compared to sensor inputs. I will use polling. 
 * 
 * I implemented MoveUp but the other 5 Move* are no different.
 * 
 * To avoid confusing, I renamed the Land command to TouchDown.
 * 
 * As a bonus, I made provisions for composite commands like
 * MoveUp2MetersLeft3Meters = MoveUp -> MoveDistance(3) -> MoveLeft -> MoveDistance(3) Please 
 * see javadoc in MoveDistance class
 * 
 * <h1>====internal interface====</h1>
 * Each CommandProcessor will run a loop until target-state is reached. 
 * During the loop, if engine is found to be off (discovered via polling), target-state would change to something like LANDED.
 * 
 * Sofia gets closer to a target-state by sending internal requests to the engines. All other Sofia components are read-only sensors.
 * 
 * <h2>--target states--</h2>
 * target state LANDED == { no movement in drone or the blade; engine is effectively off (perhaps in Neutral gear)}
 * By the laws of physics, altitude has to be zero.
 * 
 * target state HOVERING == {no movement except possible spin; blade speed > 0; engine power level > minimum}
 * 
 * target state FREEFALL == {drone in motion, but all engine power levels == 0}. Need to send distress signal and send 
 * continuous requests to all engines in each loop.
 * 
 * <h2>--algorithms:--</h2>
 * For each Command, in each CommandProcessor loop iteration, Sofia makes incremental decisions about what specific requests to issue. 
 * Sofia makes these decisions based on polling sensor results, following some algorithm.  
 * 
 * Let's take Landing command as example. 

 */
package com.nsdq.drone;






















