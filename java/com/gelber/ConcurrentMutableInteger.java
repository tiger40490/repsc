package com.gelber;

import java.io.Serializable;

class ConcurrentMutableInteger implements Serializable{
	private static final long serialVersionUID = -6068045611167518235L;
	private int i = 0;

	public synchronized void increment() {
		this.i++;
	}

	public int getInt() {
		return this.i;
	}
	@Override
	public String toString() {
		return ""+this.i;
	}
}
