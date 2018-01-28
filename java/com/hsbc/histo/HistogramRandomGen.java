package com.hsbc.histo;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Random;

interface ProbabilisticRandomGen {
	public int nextFromSample();

	/**
	 * Represents a bar in a histogram
	 */
	public static class NumAndProbability {
		private final int number;
		private final float probabilityOfSample;

		public NumAndProbability(int number, float probabilityOfSample) {
			this.number = number;
			this.probabilityOfSample = probabilityOfSample;
		}

		public int getNumber() {
			return number;
		}

		public float getProbabilityOfSample() {
			return probabilityOfSample;
		}
	}
}

public class HistogramRandomGen implements ProbabilisticRandomGen {
	/**
	 * builder for the generator to compute and set up data for the generator.
	 * 
	 * Builder pattern can handle complex construction logic such as this. 
	 */
	static class Builder {
		private List<NumAndProbability> histogram;

		public Builder withHistorgram(final List<NumAndProbability> histogram) {
			this.histogram = histogram;
			return this;
		}

		public HistogramRandomGen build() {
			float _runningTotal = 0;
			final List<Float> _cummulatives = new ArrayList<Float>();
			final HashSet<Integer> seen = new HashSet<Integer>();

			for (NumAndProbability bar : histogram) {
				if (!seen.add(bar.getNumber()))
					throw new IllegalArgumentException(
							"Input integers must be unique, but found this duplicate integer : "
									+ bar.getNumber());
				if (bar.getProbabilityOfSample() <= 0)
					throw new IllegalArgumentException(
							"Non-positive probability is meaningless : "
									+ bar.getProbabilityOfSample());
				_runningTotal += bar.getProbabilityOfSample();
				_cummulatives.add(_runningTotal);
			}// now _cummulatives.size() == histogram.size()

			if (Math.abs(_runningTotal - 1) > 0.0000001)
				throw new IllegalArgumentException(
						"By definition sum of probabilities must be 100% "
								+ "(within tolerance), but I found sum = "
								+ _runningTotal);
			System.out.println(_cummulatives);
			
			return new HistogramRandomGen(
				Collections.unmodifiableList(histogram), 
				Collections.unmodifiableList(_cummulatives));
		}
	}

	final Random random = new Random();
	final List<NumAndProbability> historgram;
	
	// 0 isn't in cummulative
	final List<Float> cummulativeProbMass;

	/**
	 * There's no reason to modify any field -- UnmodifiableLists. If there's
	 * any number change in the input histogram, it's cleaner to construct a new
	 * instance.
	 * 
	 * Mutable state in this class would invite trouble in a multi-threaded
	 * environment.
	 */
	private HistogramRandomGen(final List<NumAndProbability> histogram,
			List<Float> _cummulatives) {
		this.historgram = Collections.unmodifiableList(histogram);
		this.cummulativeProbMass = Collections.unmodifiableList(_cummulatives);
	}

	/**
	 * The challenge is something like a point search among an (potentially
	 * long) ascending list of floating point numbers.
	 * <p/>
	 * Conceptually, we can visualize the histogram as a ful pie chart of N
	 * slices. Shoot an arrow to choose a slice. The size of each slice
	 * correspond to the probability of hit.
	 * <p/>
	 * Binary search is O(logN). For example, when N is 2 trillion, we need
	 * about 40 comparisons. In practice, it is realistically possible that once
	 * we construct the histogram, we need to draw from it thousands of times.
	 * It's not great if each draw takes O(logN) time. There might be a way to
	 * improve on that but I am yet to find it.
	 */
	@Override
	public int nextFromSample() {
		return nextFromSample(false, -1);
	}

	/**
	 * 
	 * @param isVerbose
	 * @param arrow
	 *            : Any negative number is equivalent -- a new uniform-random 
	 *            number will be
	 *            generated from standard uniform distribution as the 
	 *            arrow. This is the most common usage.
	 *            <p/>
	 *            If a deterministic, controlled, predictible environment is
	 *            required, a pre-set positive value can be passed in.
	 * @return the desired random output
	 */
	public int nextFromSample(final boolean isVerbose, float arrow) {
		if (arrow < 0)
			arrow = this.random.nextFloat();
		if (arrow > 1) throw new IllegalArgumentException("arrow must be a probability value");
		int _slice = Collections.binarySearch(this.cummulativeProbMass, arrow);
		/**
		 * negative _slice is normal
		 * 
		 * non-negative _slice means hitting the boundary between 2 slices. The
		 * slice "below" would be selected, in this implementation.
		 */
		int index = (_slice >= 0 ? _slice : Math.abs(_slice) - 1);
		int ret = this.historgram.get(index).getNumber();
		if (isVerbose) {
			System.out.println("Arrow ?   " + arrow);
			System.out.println("Which slice hit?   " + _slice);
			System.out.println("Which bar hit (draw output)?   " + ret);
		}
		return ret;
	}
}
