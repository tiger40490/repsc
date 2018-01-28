package com.iv.iterate;

import static java.lang.System.out;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.NoSuchElementException;

import org.junit.Before;
import org.junit.Test;

/**
 * Can run as of 2017 Feb 20
 */
public class TestFilterIteratorSingleThreaded {//v1.0
	private IObjectTest<String> filter = new FilterNegative<String>();
	private FilterIteratorImplByDecoration<String> IUT; // instance under test
	private Iterator<String> internalItr;
	private List<String> list;
	@Before
	public void setUp() {
		list = new ArrayList<String>(Arrays.asList("aa", "--", "bb", "cc",
				"dd", "--", "--", "ee", "ff", "--"));
	}

	@Test
	public void callNextAfterHasNext() {//v.9
		internalItr = list.listIterator();
		IUT = new FilterIteratorImplByDecoration<String>(internalItr, filter);
		int good = 0;
		for (; IUT.hasNext(); good++) {
			String a = IUT.next();
			out.println("good element: " + a);
		}
		assertEquals(6, good);
	}

	@Test
	public void hasNextTwiceInARow() {
		//to prove that hasNext() doesn't move internal marker!
		list = Arrays.asList("jj");
		internalItr = list.listIterator();
		IUT = new FilterIteratorImplByDecoration<String>(internalItr, filter);
		assertTrue(IUT.hasNext());
		assertTrue(IUT.hasNext());
	}

	@Test
	public void nextTwiceInARow() {
		list = new ArrayList<String>(Arrays
				.asList("aa", "--", "bb", "--", "--"));
		internalItr = list.listIterator();
		IUT = new FilterIteratorImplByDecoration<String>(internalItr, filter);
		assertEquals("aa", IUT.next());
		assertEquals("bb", IUT.next());
		try {
			IUT.next();
		} catch (NoSuchElementException e) {
			assertTrue(e + " received as expected", true);
			return;
		}
		fail("should not reach here. Should have returned.");
	}

	@Test
	public void first2ElementsBad() {//v.9
		list = Arrays.asList("-b", "--", "cc", "-d");
		internalItr = list.listIterator();
		IUT = new FilterIteratorImplByDecoration<String>(internalItr, filter);

		assertTrue(IUT.hasNext());
		assertTrue(IUT.hasNext());
		assertTrue(IUT.hasNext());
		assertTrue(IUT.hasNext());
		assertEquals("cc", IUT.next());
		assertFalse(IUT.hasNext());
		assertFalse(IUT.hasNext());
	}

	@Test
	public void last2ElementsBad() {
		list = Arrays.asList("cc", "--", "-d");
		internalItr = list.listIterator();
		IUT = new FilterIteratorImplByDecoration<String>(internalItr, filter);
		assertEquals("cc", IUT.next());
		assertFalse(IUT.hasNext());
		assertFalse(IUT.hasNext());
		assertFalse(IUT.hasNext());
		assertFalse(IUT.hasNext());
	}
}
