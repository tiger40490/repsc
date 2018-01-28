package com.hsbc.slidingWindow;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Queue;

import com.hsbc.slidingWindow.SlidingWindowStats.Statistics;

/**
 * 
 *This object is initially incomplete, until this.getSample() is called, which
 * sets up the all-important this.lazyLoadedSortedSample field.
 * 
 *This object is immutable once populated.
 * 
 *This object takes the throne as the Ticker until it becomes out of date
 * (dethroned) due to a new Measurement, unless the candidate Ticker is idential
 * in content.
 */
public class StatData implements Statistics { // v0.9
	public static final double UNINITIALIZED_STAT_VALUE = -Double.MAX_VALUE;
	private double mean = UNINITIALIZED_STAT_VALUE;
	private double mode = UNINITIALIZED_STAT_VALUE;
	private List<Double> lazyLoadedSortedSample = Collections
			.<Double> emptyList(); // default value

	/**
	 * a reference to a possibly volatile collection. Before using it, we need
	 * to make a copy. We delay the copying until needed, becasue the
	 * synchronized copying and sorting can be expensive but perhaps not needed
	 * at all.
	 */
	private final Queue<Double> rawData;

	public StatData(Queue<Double> rawData) {
		if (rawData == null || rawData.isEmpty())
			throw new IllegalArgumentException("unusable raw Data");
		this.rawData = rawData;
	}

	@Override
	public String toString() {
		String last = "no last item (empty sample)";
		if (!this.lazyLoadedSortedSample.isEmpty())
			last = ""
					+ this.lazyLoadedSortedSample.get(lazyLoadedSortedSample
							.size() - 1);
		StringBuilder builder = new StringBuilder();
		builder.append(" StatData [mean=").append(this.getMean()).append(
			", mode=").append(this.getMode()).append(", sortedSample last = ")
				.append(last).append("]");
		return builder.toString();
	}

	/**
	 * lazy calculation. Result is cached and immutable
	 */
	@Override
	public double getMean() {
		if (this.mean == UNINITIALIZED_STAT_VALUE) {
			double sum = 0;
			for (double mark : this.rawData) {
				sum += mark;
			}
			this.mean = sum / (double) this.rawData.size();
		}
		return this.mean;
	}

	/**
	 * lazy calculation. Result is cached and immutable
	 */
	@Override
	public double getMode() {
		if (this.mode == UNINITIALIZED_STAT_VALUE) {
			this.mode = getMode(this.getSample());
		}
		return this.mode;
	}

	static double getMode(List<Double> sortedSample) {
		double leader = sortedSample.get(0);
		int leaderFrequency = 1, currFrequency = 1;
		double prevValue = leader;
		boolean isLeaderOutdated = false;

		for (int i = 1; i < sortedSample.size(); ++i) {
			double tmp = sortedSample.get(i);
			if (Math.abs(tmp - prevValue) < 0.00001) {// basically same value
				if (++currFrequency > leaderFrequency)
					isLeaderOutdated = true;
				continue;
			}
			if (isLeaderOutdated) {
				leaderFrequency = currFrequency;
				leader = prevValue;
				isLeaderOutdated = false;
			}
			prevValue = tmp;
			currFrequency = 1;
		}
		return leader;
	}

	@Override
	public double getPctile(int rank) {
		return getPctile(rank, LatencyStatService.INSTANCE.getWindowSize(), this
				.getSample());
	}

	static double getPctile(int N, int size, List<Double> sample) {//v0.9
		if (1 > N || N > 100)
			throw new IllegalArgumentException(
					"Invalid percentile input. Programmer error!");
		final int target = (int) Math.ceil(N / 100.0 * size) - 1;
		System.out.println("target = " + target);
		return sample.get(target);
	}

	/**
	 * @return
	 * @return
	 */
	synchronized List<Double> getSample() {
		// isEmpty() must be inside synchronized, similar to lazy singleton
		if (!this.lazyLoadedSortedSample.isEmpty())
			return this.lazyLoadedSortedSample;

		ArrayList<Double> unsorted;
		synchronized (this.rawData) {
			/*
			 * make a copy of the queue (while holding lock on it). Unaffected
			 * by subsequent modifications.
			 */
			unsorted = new ArrayList<Double>(this.rawData);
		}
		if (this.rawData.size() != LatencyStatService.INSTANCE.getWindowSize() ) {
			throw new IllegalStateException("Queue size is wrong.");
		}
		Collections.sort(unsorted);// now sorted!
		this.lazyLoadedSortedSample = new ArrayList<Double>(Collections
				.unmodifiableList(unsorted));
		return this.lazyLoadedSortedSample;
	}
}
