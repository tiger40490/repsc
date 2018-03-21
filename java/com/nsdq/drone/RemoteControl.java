package com.nsdq.drone;

/**
 * This object is in a different JVM, whereas Sofia runs in a JVM on-board the drone.
 * 
 */
public abstract class RemoteControl {
	abstract void send(Cmd cmd);
	void sendTakeOff() {
		send(new TakeOff());
	}
	void sendMoveUp() {
		send(new MoveUp());
	}
	void sendStablize() {
		send(new Stablize());
	}
	void sendStatus() {
		send(new ShowStatus());
	}
	void sendLand() {
		send(new TouchDown());
	}
}
