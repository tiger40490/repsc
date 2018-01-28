package com.hsbc.eventBus;

import java.util.Queue;
import java.util.concurrent.CopyOnWriteArrayList;

public class WatchQueue<T extends BaseMessage> {//v1
	public final Queue<T> queue;
	
	/**
	 * A thread-safe list optimized for frequent read but infrequent write
	 */
	public final CopyOnWriteArrayList<Subscriber<T>> subscribers 
		= new CopyOnWriteArrayList<Subscriber<T>>();
	
	public WatchQueue(Queue<T> q) {
		if (q == null) throw new IllegalArgumentException("null queue");
		this.queue = q;
	}
}
