package com.hsbc.slidingWindow;

import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

public class StatDataTest {//v1.0

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
	}

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testStatic_GetMode() {
		List<Double> sortedSample = new ArrayList<Double>(Arrays.asList(2.2,
			2.2, 3.3, 3.3, 3.3, 5.5, 5.5, 5.5, 8.8, 13.1, 21.2));
		double mode = StatData.getMode(sortedSample);
		//System.out.println(mode);
		assertEquals(3.3, mode, 0.000001);
	}

	@Test
	public void testStatic_GetPctile() {
		List<Double> sortedSample = new ArrayList<Double>(
				Arrays.asList(1.5,  2.0,  3.5,  4.0,  5.0));
		assertEquals(1.5, StatData.getPctile(1, sortedSample.size(), sortedSample), 0.0001);
		assertEquals(2.0, StatData.getPctile(40, sortedSample.size(), sortedSample), 0.0001);
		assertEquals(3.5, StatData.getPctile(50, sortedSample.size(), sortedSample), 0.0001);
		assertEquals(5.0, StatData.getPctile(100, sortedSample.size(), sortedSample), 0.0001);
	}
}
