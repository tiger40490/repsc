package com.iv.iterate;

import static java.lang.System.out;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.ConcurrentModificationException;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

/**
 * Can run as of 2017 Feb 20
 */
public class TestConcurrentFilterIterator {//v.9
	private IObjectTest<String> filter = new FilterNegative<String>();
	private FilterIteratorImplByDecoration<String> IUT; // instance under test
	// private Iterator<String> internalItr;
	private List<String> list;
	private Throwable childThreadExc;

	@Before
	public void setUp() {
		this.childThreadExc = null;
		this.list = new ArrayList<String>(Arrays.asList("aa", "--", "bb", "cc",
			"dd", "--", "--", "ee", "ff"));
	}

	@Test
	public void concurrentModificationBreakingFilterIterator()
			throws InterruptedException {//v.9
		Thread thr0 = new Thread() {
			@Override
			public void run() {
				try {
					FilterIteratorImplByDecoration<String> IUT0 = new FilterIteratorImplByDecoration<String>(
							list.listIterator(), filter);
					assertEquals("aa", IUT0.next());
					dump(1, IUT0);
					assertEquals("bb", IUT0.next());
					dump(2, IUT0);
					IUT0.next();
					dump(3, IUT0);
					synchronized (Object.class) {
						try {
							out.println("entering wait() to be notified...");
							Object.class.wait();
							out.println("leaving wait()");
						} catch (InterruptedException e) {
						}
					}
					dump(4, IUT0);
					try {
						IUT0.hasNext();
					} catch (ConcurrentModificationException e) {
						assertTrue(e + " expected and caught", true);
						return;
					}
					fail("should not reach here. Should have returned.");
				} catch (Throwable e) {
					e.printStackTrace();
					childThreadExc = e;
				}
			}
		};
		thr0.start();

		Thread thr1 = new Thread() {
			@Override
			public void run() {
				try {
					FilterIteratorImplByDecoration<String> IUT1 = new FilterIteratorImplByDecoration<String>(
							list.listIterator(), filter);
					dump(101, IUT1);
					assertTrue(IUT1.hasNext());
					try {// to make sure the other thread goes into wait()
						Thread.sleep(100);
					} catch (InterruptedException e) {
					}
					list.add(0, "BIG_CAT");
					dump(102, IUT1);
					synchronized (Object.class) {
						Object.class.notify();
					}
					dump(103, IUT1);
				} catch (Throwable e) {
					e.printStackTrace();
					childThreadExc = e;
				}
			}
		};
		thr1.start();
		thr1.join();
		thr0.join();
		assertNull(this.childThreadExc);
	}

	@Test
	public void twoFilterIterators_In2threads() throws InterruptedException {//v.9
		this.list.add("+g");
		this.list.add("+h");
		IUT = new FilterIteratorImplByDecoration<String>(list.listIterator(),
				filter);
		Thread thr0 = new Thread() {
			@Override
			public void run() {
				try {
					assertEquals("aa", IUT.next());
					dump(1, IUT);
					assertEquals("bb", IUT.next());
					dump(2, IUT);
					synchronized (Object.class) {
						try {
							out
									.println("entering wait() to give way to other threads");
							Object.class.wait();
							out.println("leaving wait()");
						} catch (InterruptedException e) {
						}
					}
					dump(3, IUT);
					assertEquals("cc", IUT.next());
				} catch (Throwable e) {
					e.printStackTrace();
					childThreadExc = e;
				}
			}
		};
		thr0.start();

		final FilterIteratorImplByDecoration<String> IUT1 = 
			new FilterIteratorImplByDecoration<String>(list.listIterator(),
					new FilterPositive<String>());

		Thread thr1 = new Thread() {
			@Override
			public void run() {
				try {
					dump(101, IUT1);
					assertTrue(IUT1.hasNext());
					try {// to make sure the other thread is in wait()
						Thread.sleep(1000);
					} catch (InterruptedException e) {
					}
					dump(102, IUT1);
					assertEquals("+g", IUT1.next());
					assertEquals("+h", IUT1.next());
					synchronized (Object.class) {
						Object.class.notify();
					}
				} catch (Throwable e) {
					e.printStackTrace();
					childThreadExc = e;
				}
			}
		};
		thr1.start();
		thr1.join();
		thr0.join();
		assertNull(this.childThreadExc);
	}
	@Test
	public void oneFilterIteratorsIn2threads() throws InterruptedException {
		IUT = new FilterIteratorImplByDecoration<String>(list.listIterator(),
				filter);
		Thread thr0 = new Thread() {
			@Override
			public void run() {
				try {
					assertEquals("aa", IUT.next());
					dump(1, IUT);
					assertEquals("bb", IUT.next());
					dump(2, IUT);
					synchronized (Object.class) {
						try {
							out
									.println("entering wait() to give way to other threads");
							Object.class.wait();
							out.println("leaving wait()");
						} catch (InterruptedException e) {
						}
					}
					dump(3, IUT);
					assertEquals("ff", IUT.next());
				} catch (Throwable e) {
					e.printStackTrace();
					childThreadExc = e;
				}
			}
		};
		thr0.start();

		Thread thr1 = new Thread() {
			@Override
			public void run() {
				try {
					dump(101, IUT);
					assertTrue(IUT.hasNext());
					try {// to make sure the other thread is in wait()
						Thread.sleep(1000);
					} catch (InterruptedException e) {
					}
					dump(102, IUT);
					assertEquals("cc", IUT.next());
					assertEquals("dd", IUT.next());
					assertEquals("ee", IUT.next());
					synchronized (Object.class) {
						Object.class.notify();
					}
				} catch (Throwable e) {
					e.printStackTrace();
					childThreadExc = e;
				}
			}
		};
		thr1.start();
		thr1.join();
		thr0.join();
		assertNull(this.childThreadExc);
	}
	private void dump(int i, FilterIteratorImplByDecoration<String> it) {
		out.println(Thread.currentThread().getName() + " (" + i + ") " + list
				+ " -> " + it.getColor() + "-" + it.getNextGood());
	}
}