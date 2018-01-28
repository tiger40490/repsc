package com.hsbc.eventBus;

import java.util.ArrayDeque;
import java.util.concurrent.ConcurrentLinkedQueue;

/**
 * Each message type (such as PriceMessage) gets a event bus, which is largely
 * concurrent and unaffected by RateMessages. The only way these 2 message types
 * interfere is the shared Dispatcher thread.
 * 
 * @param <T>
 *            message type
 */
public class ConcurrentEventBus<T extends BaseMessage> implements EventBus<T> {// v0.9
	private WatchQueue<T> watchQueue = new WatchQueue<T>(//v0.9
	// ArrayDeque indicates as a dummy queue:
			new ArrayDeque<T>());

	@SuppressWarnings("unchecked")
	synchronized private void initializeMyQueue(Class<T> messageType) {
		if (ConcurrentLinkedQueue.class.isInstance(this.watchQueue.queue))
			return;

		/*
		 * get() will surely return the a watch queue for tyep T, so the
		 * compiler warning is unnecessary.
		 */
		this.watchQueue = (WatchQueue<T>) Dispatcher.INSTANCE.allKnownMessageQueues
				.get(messageType);
	}

	@Override
	synchronized public void addSubscriber(Class<T> messageType, Subscriber<T> sub) {
		this.initializeMyQueue(messageType);
		this.watchQueue.subscribers.add(sub);
	}

	@Override
	synchronized public void addSubscriberForFilteredEvents(Class<T> messageType,
			Subscriber<T> sub) {
		this.addSubscriber(messageType, sub);
	}

	@Override
	public void publishEvent(T msg) {
		if (!ConcurrentLinkedQueue.class.isInstance(this.watchQueue.queue)) {
			System.out
					.println("no subscriber on this message type yet.(dummy queue found)");
			return;
		}else if (msg.isConflating()) {
			int removed = 0;
			while (true) {
				/*
				 * AbstractMessage.equals() method ensures instances of the same
				 * symbol are considered equal
				 */
				if (!watchQueue.queue.remove(msg))
					break; // nothing more to remove
				removed++;
			}
			System.out.println("[Thread # " + Thread.currentThread().getName()
					+ " ] Incoming message is conflating: " + msg
					+ " Obsolete messages removed = " + removed);
		}
		watchQueue.queue.offer(msg);

		System.out.println("[Thread # " + Thread.currentThread().getName()
				+ " ] publishing message " + msg);
		synchronized (Dispatcher.INSTANCE) {
			// the notified thread will run a method to check
			// allKnownMessageQueues.
			Dispatcher.INSTANCE.notify();
			//System.out.println("[Thread # " + Thread.currentThread().getName() + " ] notification sent");
		}
	}
}