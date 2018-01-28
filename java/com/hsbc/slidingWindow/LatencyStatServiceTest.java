package com.hsbc.slidingWindow;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotSame;
import static org.junit.Assert.assertSame;

import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import com.hsbc.slidingWindow.SlidingWindowStats.Statistics;

public class LatencyStatServiceTest {//v0.9

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
	}

	@Before
	public void setUp() throws Exception {

	}

	@After
	public void tearDown() throws Exception {
		LatencyStatService.INSTANCE.clearAll();
	}

	@Test
	public void testAsynchronous_2Subscribers_with_filter() {
		Predicate pred_ = new Predicate() {
			@Override
			public boolean isRelevant(StatData message) {
				return message.getMean() > 41;
			}
		};
		LatencyStatService.INSTANCE.subscribeForStatistics(new StatSubscriber(
				'1'));
		LatencyStatService.INSTANCE.subscribeForStatistics(new StatSubscriber(
			'2', pred_));		
		LatencyStatService.INSTANCE.add(new LatencyMeasurement(40));
		LatencyStatService.INSTANCE.add(new LatencyMeasurement(41));
		LatencyStatService.INSTANCE.add(new LatencyMeasurement(41));
		// by now, a StatData is generated but filtered out for subscriber #2

		// after the next add(), a new StatData will pass Subscriber#2's filter and
		// hit onMsg()
		LatencyStatService.INSTANCE.add(new LatencyMeasurement(44));
	}

	@Test
	public void testSynchronous_GetLatestStatistics() {
		int a = 30, b = 31, c = 34;
		LatencyStatService.INSTANCE.add(new LatencyMeasurement(a));
		LatencyStatService.INSTANCE.add(new LatencyMeasurement(b));
		LatencyStatService.INSTANCE.add(new LatencyMeasurement(b));
		Statistics stat = LatencyStatService.INSTANCE.getLatestStatistics();
		assertEquals(stat.getMean(), (a + b + b) / 3.0, 0.0001);

		LatencyStatService.INSTANCE.add(new LatencyMeasurement(c));
		stat = LatencyStatService.INSTANCE.getLatestStatistics();
		assertEquals(stat.getMean(), (b + b + c) / 3.0, 0.0001);

		LatencyStatService.INSTANCE.add(new LatencyMeasurement(c));
		LatencyStatService.INSTANCE.add(new LatencyMeasurement(a));

		assertNotSame(stat, LatencyStatService.INSTANCE.getLatestStatistics());
		stat = LatencyStatService.INSTANCE.getLatestStatistics();
		assertEquals(stat.getMean(), (c + c + a) / 3.0, 0.0001);

		LatencyStatService.INSTANCE.add(new LatencyMeasurement(c));
		assertSame("no numerical change, so ticker was not updated/replaced.", 
			stat, LatencyStatService.INSTANCE.getLatestStatistics());
	}
}