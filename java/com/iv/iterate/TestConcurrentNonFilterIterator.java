package com.iv.iterate;

import static java.lang.System.out;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.util.Arrays;
import java.util.Collections;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.junit.Test;

/** NOT testing the filtering iterator, but a simple test framework
 * to test any iterator.
 * 
 * Can run as of 2017 Feb 20
 */
public class TestConcurrentNonFilterIterator { //v1.0
	private final static List<String> SIMPLE_INPUT_LIST = 
		Collections.unmodifiableList(Arrays.asList("aa", "bb","cc", "dd", "ee"));
	static final String THREAD_B_OK = "THREAD_B_OK";
	static final String THREAD_A_OK = "THREAD_A_OK";
	
	// CME    means ConcurrentModificationException
	
	@Test
	public void noCME_In2Iterators1thread_NoInteference() {
		List<String> list = SIMPLE_INPUT_LIST;
		Iterator<String> itr1 = list.iterator();
		itr1.next();
		itr1.next();
		String thirdItem = itr1.next();
		assertEquals("cc", thirdItem);
		
		Iterator<String> itr2 = list.iterator();
		String k = itr2.next();
		assertEquals("aa", k);
		
		String m = itr1.next(); //1st instance
		assertEquals("dd", m);	
	}
	
	String[] threadResult = {"", "", ""};
	@Test
	public void noCME_In2threadsNoInterference() throws InterruptedException {
		final List<String> list = SIMPLE_INPUT_LIST;
		Thread thrA = new Thread() {
			@Override
			public void run() {
				threadResult[1] = "";
				Iterator<String> itr1 = list.iterator();
				assertEquals("aa", itr1.next());
				out.println(Thread.currentThread() + itr1.next());
				try {
					Thread.sleep(1);
				} catch (InterruptedException e) {}
				out.println(Thread.currentThread() + itr1.next());
				assertEquals("dd", itr1.next());
				threadResult[1] = THREAD_A_OK;
			}
		};
		thrA.start();

		Thread thrB = new Thread() {
			@Override
			public void run() {
				threadResult[2] = "";
				Iterator<String> itr2 = list.iterator();
				assertEquals("aa", itr2.next());
				out.println(Thread.currentThread() + itr2.next());
				try {
					Thread.sleep(1);
				} catch (InterruptedException e) {}
				out.println(Thread.currentThread() + itr2.next());
				out.println(Thread.currentThread() + itr2.next());
				assertEquals("ee", itr2.next());
				threadResult[2] = THREAD_B_OK;
			}
		};
		thrB.start();
		thrB.join();
		thrA.join();
		assertEquals(THREAD_A_OK, threadResult[1]);
		assertEquals(THREAD_B_OK, threadResult[2]);
	}

	@Test
	public void CME1thread() {
		List<String> mutableList = new LinkedList<String>(SIMPLE_INPUT_LIST);
		Iterator<String> itr = mutableList.iterator();
		assertEquals("aa",itr.next());
		Collections.reverse(mutableList); 
		assertEquals("reverse() won't trigger CME", "dd", itr.next());
		mutableList.add(0, "extra1"); //prepend
		try {
			itr.next();
		} catch (ConcurrentModificationException e) {
			out.println(e + " received as expected!");
			assertTrue("CME expected", true);
			return;
		}
		fail();
	}
}
