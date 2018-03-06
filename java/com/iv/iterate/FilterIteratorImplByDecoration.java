package com.iv.iterate;

import static java.lang.System.out;

import java.util.Iterator;
import java.util.NoSuchElementException;

/** This class is the "real" implementation. Non-trivial logic.
 *
 * Concurrency environment:
 * <ol>
 * <li>Underlying collection is shared and mutable, subject to concurrent
 * modifications. This class has no control.
 * 
 * <li>The Internal iterator passed in is stateful (it can be at the beginning,
 * middle or end of the collection), and is subject to concurrent state change.
 * This class has limited control over it.
 * 
 * <li>This object has additional state, in terms of the mutable fields. This
 * class has control of them.
 * </ol>
 * 
 * Concurrency policy
 * <ul>
 * <li>Once "this" object becomes a wrapper of this.itr, we want no other
 * wrappers to modify state of this.itr concurrently. In other words, a wrapper
 * is an owner and ownership is exclusive.
 * <li>We also want control over concurrent state changes of "this" object
 * itself. The field "this.itr" is a suitable lock again. For example, we don't
 * wan multiple threads to change this.nextGood field concurrently.
 * <li>Therefore, a lot of operations are synchronized on this.itr.
 * </ul>
 */
class FilterIteratorImplByDecoration<E> implements Iterator<E> {// v0.7
	private final IObjectTest<E> _filter;
	private final Iterator<E> _marker;
	/** next good item to be issued to caller. Could be null */
	private volatile E _nextGood = null;
	/** instrumentation and book-keeping */
	private volatile int _badCount, _goodCount;
	/**
	 * Each FilterIteratorImplByDecoration instance has exactly 1 color at any
	 * time, indicating its state. All concurrent threads should see a
	 * consistent snapshot view.
	 */
	private volatile Color currentColor = Color.BROWN;

	private enum Color {
		/**
		 * BROWN means next() was just called, and this.nextGood was issued to
		 * caller, and hasNext() has not run since. this.nextGood is currently
		 * empty
		 * 
		 * BROWN can also mean none of next() or hasNext() has been called. So
		 * this.nextGood is not populated
		 */
		BROWN,

		/**
		 * GREEN means hasNext() was just called, marker just moved and
		 * this.nextGood is populated, waiting to be issued
		 */
		GREEN,

		/**
		 * BLACK means marker has reached end of the collection, so next() will
		 * throw exception
		 * 
		 */
		BLACK;
	}

	public FilterIteratorImplByDecoration(Iterator<E> _itr,
			IObjectTest<E> _filter) {
		if (_itr == null)
			throw new IllegalArgumentException();
		if (_filter == null)
			throw new IllegalArgumentException();
		this._filter = _filter;
		this._marker = _itr;
	}

	E getNextGood() {
		return _nextGood;
	}

	private void setColor(Color c) {
		if (c == null)
			throw new IllegalArgumentException();
		synchronized (this._marker) {
			this.currentColor = c;
		}
	}

	Color getColor() {
		if (this.currentColor == null)
			throw new IllegalStateException("color is null. Programmer error");
		return this.currentColor;
	}

	/**
	 * It's impossible to simply check this.itr.hasNext(), without advancing the
	 * internal marker. When caller sends the hasNext() message asking
	 * "Any Good element remaining?" we have to physically advance the marker
	 * repeatedly until we find a Good element or reach end of the collection.
	 * 
	 * Note it's not enough to rely on the lock in moveMarker(). Without locking
	 * inside hasNext(), 2 threads might concurrently try to execute
	 * this.moveMarker(). The 2nd to enter this.moveMarker() will trigger
	 * AssertionError.
	 * 
	 * hasNext() sounds like an read-only operation like a
	 * "const member function" in c++ lingo, but in our case, it has to be a
	 * mutator method.
	 * 
	 * Could be called repeatedly by multiple threads.
	 */
	@Override
	public boolean hasNext() {
		synchronized (this._marker) {
			if (this.getColor() == Color.GREEN)
				return true;
			this.moveMarker();
			if (this.getColor() == Color.BLACK)
				return false;
			assert this.getColor() == Color.GREEN;
			return true;
		}
	}

	/**
	 * could be called repeatedly by multiple threads, resulting in interleaving
	 * behavior. However, Two concurrent callers should never get the same
	 * object (identity-wise) without advancing marker.
	 * 
	 * This metod is not read-only operation. It can trigger moveMarker() via
	 * hasNext()
	 */
	@Override
	public E next() {
		synchronized (this._marker) {
			if (!hasNext())
				throw new NoSuchElementException(
						"marker is at end of underlying collection");
			assert this.currentColor == Color.GREEN;
			this.setColor(Color.BROWN);
			return this._nextGood;
		}
	}

	/**
	 * This method attempts to move the internal marker to the next GOOD element
	 * and put it into this.nextGood field.
	 * 
	 * Must manage this.nextGood.
	 * 
	 * Method can be called repeatedly even after reaching end of the collection.
	 */
	private void moveMarker() {
		synchronized (this._marker) {
			if (this.getColor() == Color.BLACK)
				return;
			assert this.getColor() == Color.BROWN;
			out.println(Thread.currentThread().getName()
					+ " before move, nextGood = " + getNextGood());
			while (_marker.hasNext()) {// forward scan seeking next GOOD item
				final E nullableNext = _marker.next();
				if (this._filter.test(nullableNext)) {
					this._nextGood = nullableNext;
					this._goodCount++;
					this.setColor(Color.GREEN);
					out.println(Thread.currentThread().getName()
							+ " after move, nextGood = " + getNextGood());
					return;
				}
				this._badCount++;
			}
			this.setColor(Color.BLACK);
		}
	}

	/**
	 * remove() method is usually unimplemented in production code, since there
	 * are cleaner, safer ways to remove elements. In contrast, the iterator
	 * remove() method is hard to use correctly and often causes exceptions. See
	 * https
	 * ://docs.oracle.com/javase/7/docs/api/java/util/Iterator.html#remove()
	 * 
	 * My implementation here is experimental. If it doesn't work reliably in
	 * practice, just throw UnsupportedOperationException.
	 */
	@Override
	public void remove() {
		synchronized (this._marker) {
			_marker.remove(); // could throw exception
		}
	}
}
