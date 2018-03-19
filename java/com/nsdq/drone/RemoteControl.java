package com.nsdq.drone;

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
		send(new Status());
	}
	void sendLand() {
		send(new TouchDown());
	}
}
