package com.hsbc.slidingWindow;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Executors;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.ThreadPoolExecutor;

public class LatencyStatService implements SlidingWindowStats<LatencyMeasurement> {//v0.9
	public static final int THREADS_IN_POOL = 3;
	public static final int DEFAULT_WINDOW = 3;
	public static final LatencyStatService INSTANCE = new LatencyStatService();

	public final ConcurrentLinkedQueue<Double> movingWindow 
		= new ConcurrentLinkedQueue<Double>();
	private final List<StatSubscriber> subscribers = new LinkedList<StatSubscriber>();

	public final ThreadPoolExecutor eService = (ThreadPoolExecutor) Executors
			.newFixedThreadPool(THREADS_IN_POOL);
	private StatData ticker; //live ticker

	private int windowSize = DEFAULT_WINDOW;

	public int getWindowSize() {
		return this.windowSize;
	}

	/**setWindowSize() is an experimental feature.
	 * 
	 * Won't affect any existing sortedSample, becuase each sortedSample is a
	 * copy.
	 * 
	 * Still, this operation is tricky when inter-thread communications (such as
	 * new-sample notification) are taking place.
	 */
	synchronized public void setWindowSize(int newSize) {
		if (newSize <= 0)
			throw new IllegalArgumentException("non-positive window size");
		this.windowSize = newSize;

		if (newSize < movingWindow.size()) {
			shrinkWindow();
		}
	}

	synchronized private void shrinkWindow() {//v1.0
		for (int howManyRemoved = 1;; ++howManyRemoved) {
			Double removedItem = this.movingWindow.poll();

			if (this.movingWindow.size() <= this.getWindowSize()) {
				System.out.println(howManyRemoved // usually 1
					+ " measurement(s) removed"); 
				return;
			}
			if (removedItem == null) 
				throw new IllegalStateException(
						"queue has become empty during shrink()");
		}
	}

	/**
	 * Most parts of this method is thread-safe and needs no locking
	 */
	@Override
	public void add(LatencyMeasurement measurement) {//v1.0
		this.movingWindow.offer((double) measurement.intValue() );
		System.out.println("[Thread # " + Thread.currentThread().getName()
				+ " ]\n enqueued new measurement: " + measurement);
		int excess = this.movingWindow.size() - this.getWindowSize();
		if (excess < 0) {
			return;
		} else if (excess > 0) {
			System.out
					.println("Removing earlier measurements (if any) -- sliding the window ...");
			shrinkWindow();
		}

		final StatData candidate = new StatData(this.movingWindow);
		if (null != ticker && ticker.getSample().equals(candidate.getSample())) {
			// equals() checks sorted list contents
			System.out.println("No change in sample:");
			System.out.println(ticker.getSample());
			System.out.println(candidate.getSample());
			return;
		}
		this.ticker = candidate;

		// now send ticker to each subscribers
		for (StatSubscriber sub : subscribers) {
			if (sub == null)
				throw new IllegalStateException(
						"null subscriber found. Programmer error!");
			CallbackTask task = new CallbackTask(this.ticker, sub);
			if (task.isRelevant)
				this.dispatch(task);
			else
				System.out.println("[Thread # "
						+ Thread.currentThread().getName()
						+ " ]\n filtered out new stat: " + this.ticker + sub);
		}
	}

	/**
	 * This method submits a single Callable task to thread pool
	 * 
	 * @param taskInput
	 *            used to create a runnable task
	 */
	private void dispatch(Callable<Character> callable) {
		CallbackTask callbackTask = (CallbackTask) callable;
		System.out.println("[Thread # " + Thread.currentThread().getName()
				+ " ]\n adding task to thread pool. stats = " + callbackTask.msg
				+ callbackTask.sub);
		for (int retry = 0;retry <= 1;++retry) {
			try {
				callable = new Callable<Character>() {
					@Override
					public Character call() throws Exception {
						System.out.println(" -- dummy Callable executing in thread pool --");
						return 0;
					}
				};// test for RejectedExecutionException
				this.eService.submit(callbackTask);
				break;
			} catch (RejectedExecutionException e) {
				e.printStackTrace();
				System.err.println("---- ^  ^    Task rejected      ^  ^ ----");
			}
		}
	}

	@Override
	public Statistics getLatestStatistics() {
		if (this.ticker == null)
			return null;
		System.out.println(this.ticker);
		return this.ticker;
	}

	@Override
	synchronized public void subscribeForStatistics(StatSubscriber sub) {
		this.subscribers.add(sub);
	}

	@Override
	synchronized public void clearAll() {
		this.movingWindow.clear();
		this.subscribers.clear();
		//System.out.println("      queue and thread pool all cleared\n");
	}
}
