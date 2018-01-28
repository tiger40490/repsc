package com.hsbc.histo;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.SortedMap;
import java.util.TreeMap;

import org.junit.Test;

import com.hsbc.histo.ProbabilisticRandomGen.NumAndProbability;

public class HistogramRandomGenTest {
	private static List<NumAndProbability> input;
	private static final SortedMap<Integer, Float> myMap;
	static {
		myMap = new TreeMap<Integer, Float>();
		myMap.put(10, 0.1f);
		myMap.put(32, 0.2f);
		myMap.put(63, 0.3f);
		myMap.put(104, 0.4f);
		List<NumAndProbability> _input = new ArrayList<NumAndProbability>();
		for (int key : myMap.keySet()) {
			_input.add(new NumAndProbability(key, myMap.get(key)));
		}
		input = Collections.unmodifiableList(_input);
	}
	@Test
	public void testBuilder() {
		HistogramRandomGen gen = new HistogramRandomGen.Builder()
				.withHistorgram(input).build();
		assertEquals(input.size(), gen.cummulativeProbMass.size());

		// 
		List<NumAndProbability> dupeInput = new ArrayList<NumAndProbability>(
				input);
		dupeInput.add(new NumAndProbability(10, 0.4f));
		Object dummy = null;
		try {
			dummy = new HistogramRandomGen.Builder().withHistorgram(dupeInput)
					.build();
			fail("should not reach here");
		} catch (IllegalArgumentException e) {
			assertTrue("IllegalArgumentException expected", true);
			System.out.println(e.getMessage());
		}
		assertNull(dummy);

		// probability numbers don't add up to 100%
		List<NumAndProbability> badInput = new ArrayList<NumAndProbability>(
				input);
		badInput.remove(0);
		try {
			dummy = new HistogramRandomGen.Builder().withHistorgram(badInput)
					.build();
			fail("should not reach here");
		} catch (IllegalArgumentException e) {
			assertTrue("IllegalArgumentException expected", true);
			System.out.println(e.getMessage());
		}
		assertNull(dummy);
	}

	/**
	 * Test method for
	 * {@link com.hsbc.histo.HistogramRandomGen#nextFromSample()}.
	 */
	@Test
	public void testRepeatedDraws() {
		HistogramRandomGen gen = new HistogramRandomGen.Builder()
				.withHistorgram(input).build();
		HashMap<Integer, Integer> counter = new HashMap<Integer, Integer>();
		for (NumAndProbability bar : input) {
			counter.put(bar.getNumber(), 0);// init
		}
		int howManyDraws = 3987654;
		for (int i = 0; i < howManyDraws; ++i) {
			int draw = gen.nextFromSample();
			counter.put(draw, 1 + counter.get(draw));
		}
		int sum = 0;
		for (Map.Entry<Integer, Integer> entry : counter.entrySet()) {
			int key = entry.getKey(), count = entry.getValue();
			sum += entry.getValue();
			final float actual = (float) count / howManyDraws;
			assertEquals(myMap.get(key), actual, .0005);
			System.out.println(key + " \t -> " + actual);
		}
		assertEquals(howManyDraws, sum);
	}

	@Test
	public void testBoundaryBetween2slices() {
		HistogramRandomGen gen = new HistogramRandomGen.Builder()
				.withHistorgram(input).build();
		assertEquals(10, gen.nextFromSample(true, 0));
		assertEquals(32, gen.nextFromSample(true, 0.3f));
		// Above: hitting the boundary
		// Below: slightly above boundary
		assertEquals(63, gen.nextFromSample(true, 0.30001f));
	}
}
