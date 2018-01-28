package com.hsbc.eventBus;

import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

public class Dispatcher implements Runnable {// v0.9
	public static final int HOW_MANY_THREAD_IN_POOL = 2;
	public final ThreadPoolExecutor eService = (ThreadPoolExecutor) Executors
			.newFixedThreadPool(HOW_MANY_THREAD_IN_POOL);

	public final Map<Class<? extends BaseMessage>, WatchQueue<? extends BaseMessage>> allKnownMessageQueues = new ConcurrentHashMap<Class<? extends BaseMessage>, WatchQueue<? extends BaseMessage>>();
	public final static Dispatcher INSTANCE = new Dispatcher();

	private Dispatcher() {
		// every message type should have one queue
		allKnownMessageQueues.put(PriceMessage.class,
			new WatchQueue<PriceMessage>(
			// queue with unlimited capacity, so producer never blocks
					new ConcurrentLinkedQueue<PriceMessage>()));
		allKnownMessageQueues.put(BondPriceMessage.class,
			new WatchQueue<BondPriceMessage>(
					new ConcurrentLinkedQueue<BondPriceMessage>()));
	}

	public void clearAll() {
		for (Class<? extends BaseMessage> clazz : this.allKnownMessageQueues
				.keySet()) {
			this.allKnownMessageQueues.get(clazz).queue.clear();
		}
	}

	/**
	 * endless loop to check allKnownMessageQueues, blocking in wait() if empty.
	 * For every Message found, create task and dispatch to thread pool.
	 * 
	 * Work done on this thread had better be fast.
	 */
	@Override
	public void run() { // v0.9
		for (;;) {
			if (sweepAllKnownQueuesOnce()) {
				System.out
						.println("[Thread # "
								+ Thread.currentThread().getName()
								+ " ] Last sweep found some new message, so let's sweep again.");
				continue;
			}

			System.out.println("[Thread # " + Thread.currentThread().getName()
					+ " ] All known queues are empty in the last sweep. "
					+ "Dispatcher thread going back into wait()");
			try {
				/*
				 * This method only runs on dispatcher thread, so "synrhonized"
				 * would introduce minimal performance cost. In other words, the
				 * lock is likely uncontested.
				 */
				synchronized (Dispatcher.INSTANCE) {
					/*
					 * When this thread gets notified, it will set
					 * noMessageFound to true and and check
					 * allKnownMessageQueues repeatedly, until noMessageFound
					 * 
					 * In the case of spurious wake-up, this thread would simply
					 * check all queues. If all empty, then go back to wait().
					 */
					Dispatcher.INSTANCE.wait();
				}
				System.out.println("[Thread # "
						+ Thread.currentThread().getName()
						+ " ] leaving wait()");

			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		} // for (;;)
	}

	/**
	 * This method checks each message queue exactly once. Suppose PriceMessage
	 * queue has 3 subscribers. For each Price Message found, it creates 3 tasks
	 * for the subscribers and dispatches to the thread pool.
	 * 
	 * This method only runs on dispatcher thread, so "synrhonized" would
	 * introduce minimal performance cost. In other words, the lock is likely
	 * uncontested, so the default biased lock JVM feature would kick in
	 * 
	 * @return true if the sweep found any message, so the calling method should
	 *         probably sweep again. A sweep could take hundreds of clock
	 *         cycles. During such a sweep, new messages could come in
	 *         concurrently, which would NOT be picked up in this sweep. So a
	 *         re-check is needed. If the re-check is an empty sweep it would be
	 *         super-fast and low-cost in terms of performance.
	 */
	private synchronized boolean sweepAllKnownQueuesOnce() {// v0.9
		boolean isEmptySweep = true;
		for (Class<? extends BaseMessage> clazz : this.allKnownMessageQueues
				.keySet()) {
			WatchQueue<? extends BaseMessage> watchQueue = this.allKnownMessageQueues
					.get(clazz);
			for (;;) {
				BaseMessage msg = watchQueue.queue.poll();
				if (msg == null)
					break; // this queue is empty. Check next queue
				isEmptySweep = false;

				/*
				 * Now dispatch to everyone who subscribes to this queue.
				 * 
				 * This loop runs on Dispatcher thread and is designed to be
				 * fast and cheap. The actual callback functions run on the
				 * worker threads.
				 */
				for (Subscriber<? extends BaseMessage> sub : watchQueue.subscribers) {
					if (sub == null)
						throw new IllegalStateException(
								"null subscriber found in QueueWithSubscribers. Programmer error!");
					CallbackTask<? extends BaseMessage> task = CallbackTask
							.create(msg, sub);
					if (task.isRelevant)
						this.dispatch(task);
					else
						System.out.println("[Thread # "
								+ Thread.currentThread().getName()
								+ " ]\n filtered out a msg: " + msg + sub);

				}
			}// done checking one queue
		}// all known queues checked
		return !isEmptySweep;
	}

	/**
	 * This method submits a single Callable task to thread pool
	 * 
	 * @param taskInput
	 *            used to create a runnable task
	 */
	private void dispatch(Callable<Character> callbackTask) {
		CallbackTask<?> tmp = (CallbackTask<?>) callbackTask;
		System.out
				.println("[Thread # " + Thread.currentThread().getName()
						+ " ]\n adding task to thread pool. msg = " + tmp.msg
						+ tmp.sub);
		this.eService.submit(callbackTask);
	}
}
