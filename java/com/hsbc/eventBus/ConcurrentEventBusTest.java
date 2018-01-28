package com.hsbc.eventBus;

import static org.junit.Assert.assertTrue;

import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

public class ConcurrentEventBusTest {
	ConcurrentEventBus<PriceMessage> pxMsgBus;
	ConcurrentEventBus<BondPriceMessage> bondMsgBus;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		new Thread(Dispatcher.INSTANCE, "Dispatcher").start();
	}

	@Before
	public void setUp() throws Exception {
		this.pxMsgBus = new ConcurrentEventBus<PriceMessage>();
		this.bondMsgBus = new ConcurrentEventBus<BondPriceMessage>();
	}

	@After
	public void tearDown() throws Exception {
		Dispatcher.INSTANCE.clearAll();
	}

	static private void drainThreadPool() {
		for (;;) {
			long submitted = Dispatcher.INSTANCE.eService.getTaskCount();
			long completed = Dispatcher.INSTANCE.eService
					.getCompletedTaskCount();
			if (submitted <= completed) // approximate
				break;
			System.out.println(submitted + " submitted to thread pool");
			System.out.println(completed + " completed by thread pool");
			Thread.yield(); // let the thread pool drain off
		}
		for (int i = 0; i < 5; ++i)
			Thread.yield();
		System.out.println("----------------------------");
	}

	@Test
	public void testConflation() {// v1
		this.pxMsgBus.addSubscriber(PriceMessage.class, new PriceSubscriber());
		this.pxMsgBus.publishEvent(new PriceMessage("GOOG", 4901, false));
		this.pxMsgBus.publishEvent(new PriceMessage("GOOG", 4902, false));

		/**
		 * Message below could remove 0, 1 or 2 previous messages. Depends on
		 * how many of them are in queue and how many are sent to thread pool
		 */
		this.pxMsgBus.publishEvent(new PriceMessage("GOOG", 5401, true));
		Thread.yield();
		this.pxMsgBus.publishEvent(new PriceMessage("GOOG", 4903, false));
		this.pxMsgBus.publishEvent(new PriceMessage("GOOG", 4904, false));
		/**
		 * Message below could remove 0, to 5 previous messages. Depends on how
		 * many of them are in queue and how many are sent to thread pool
		 */
		this.pxMsgBus.publishEvent(new PriceMessage("GOOG", 5402, true));
		assertTrue("no error means all good", true);
		Thread.yield();
		Thread.yield();
		drainThreadPool();
	}

	@Test
	public void testFilter() {// v1
		Predicate<PriceMessage> pred_ = new Predicate<PriceMessage>() {
			@Override
			public boolean isRelevant(PriceMessage message) {
				return message.priceInCents > 5001;
			}
		};
		// add a filtered subscriber
		this.pxMsgBus.addSubscriber(PriceMessage.class, new PriceSubscriber(
				'1', pred_));
		this.pxMsgBus.publishEvent(new PriceMessage("APPL", 4900, false));
		this.pxMsgBus.publishEvent(new PriceMessage("APPL", 5200, false));
		assertTrue("no error means all good", true);
		drainThreadPool();
	}

	@Test
	public void testPublish2subscribersOnSameQueue() {// v1
		this.pxMsgBus.addSubscriber(PriceMessage.class,
			new PriceSubscriber('1'));
		this.pxMsgBus.publishEvent(new PriceMessage("1REC", 5100, false));
		Thread.yield(); // With yield(), Only one subscribe should receive the
		// above message.
		// 2 subscribes should receive message below.
		this.pxMsgBus.addSubscriber(PriceMessage.class,
			new PriceSubscriber('2'));
		this.pxMsgBus.publishEvent(new PriceMessage("2REC", 7800, false));

		assertTrue("no error means all good", true);
		drainThreadPool();
	}

	@Test
	public void test2MessageTypes() {// v1
		this.bondMsgBus.addSubscriber(BondPriceMessage.class,
			new BondPriceSubscriber());
		this.bondMsgBus.publishEvent(new BondPriceMessage("10yTr", 9800, false,
				4.1));

		this.pxMsgBus.addSubscriber(PriceMessage.class,
			new PriceSubscriber('1'));
		this.pxMsgBus.publishEvent(new PriceMessage("GOOG", 3900, false));
		assertTrue("no error means all good", true);
		drainThreadPool();
	}
}
