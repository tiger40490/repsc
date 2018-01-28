package com.bgc;

import java.util.UUID;
import java.util.concurrent.atomic.AtomicInteger;

class Island {

	private static final String _DUMMY = "DUMMY";
	public static final Island DUMMY_ISLAND = new Island(_DUMMY);

	/*
	 * helps ensure smaller island merges into bigger island. (The reverse merge
	 * would be lower performance at query time.)
	 *
	 * However, under multi-threading, I find it hard to ensure 100% accuracy of
	 * this value. Therefore, this is an approximate value. 100% accuracy is not
	 * critical in this value.
	 */
	final private AtomicInteger approxSize = new AtomicInteger(0);

	final String id; // unique id
	private volatile Island mergedInto = DUMMY_ISLAND;
	public final StringBuffer debugDisplayName = new StringBuffer(); // only for
																		// debugging

	/**
	 * create a new island with 2 cities
	 * 
	 * @param city1
	 * @param city2
	 */
	Island(String city1, String city2) {
		this(UUID.randomUUID().toString());
		this.approxSize.set(2);

		// put the two founding cities in the island's displayName
		this.debugDisplayName.append(city1).append("|").append(city2);
	}

	private Island(String id) {
		if (id == null || id.isEmpty())
			throw new IllegalArgumentException();
		this.id = id;
		if (_DUMMY == this.id) {
			this.mergedInto = this;
			this.debugDisplayName.append(_DUMMY);
		}
	}

	/////////////////// fields + constructors done //////////////////
	/////////////////// fields + constructors done //////////////////
	/////////////////// fields + constructors done //////////////////

	/**
	 * V0.8 This method is always invoked while holding both locks on
	 * "this"+biggerIsland, so effectively this method has exclusive access to
	 * both islands. The data in these islands will not change beneath our feet.
	 */
	void mergeInto(Island biggerIsland) {
		assert !(this.isAcquired() || biggerIsland
				.isAcquired()) : "calling method should have checked this condition, while holding locks";
		assert this.approxSize.get() <= biggerIsland.approxSize
				.get() : "calling method should have checked this condition, while holding locks";

		this.setRedirect(biggerIsland);
		biggerIsland.approxSize.addAndGet(this.approxSize.get());

		// Below step is optional, since no one would merge this island again.
		this.approxSize.set(0);
		this.debugDisplayName.insert(0, "--Acquired--");
	}

	// V1.0
	private void setRedirect(Island biggerIsland) {
		assert this != DUMMY_ISLAND : "DUMMY island should never receive this message";
		assert !this.isAcquired() : "This method shoudl only be called " + "once, and only when the pointer"
				+ "has the default value";
		if (biggerIsland == null || biggerIsland == DUMMY_ISLAND)
			throw new IllegalArgumentException();
		this.mergedInto = biggerIsland;
	}

	Island nextRedirect() {
		return this.mergedInto;
	}

	boolean isAcquired() {
		return this.nextRedirect() != Island.DUMMY_ISLAND;
	}

	/**
	 * @return the final "bigger" island after following all the pointers 
	 * or "this" if this.mergedInto == DUMMY_ISLAND
	 */
	Island realRedirect() {
		for (Island ret = this;;) {
			if (ret.nextRedirect() == Island.DUMMY_ISLAND) 
				return ret;
			ret = ret.nextRedirect();
		}
	}

	/**
	 * V0.8
	 * 
	 */
	synchronized void add(String city, Graph graph) {
		assert this != DUMMY_ISLAND : "DUMMY island should never receive add() message";
		if (city == null || city.isEmpty())
			throw new IllegalArgumentException();

		/*
		 * This check has to be done while holding the lock!
		 * 
		 * Otherwise this island could get acquired concurrently, without us
		 * knowing!
		 */
		if (this.isAcquired()) {
			Island biggerIsland = this.realRedirect();
			/*
			 * No locking on biggerIsland here, to simplify concurrency design
			 * and avoid deadlock. Tradeoff -- biggerIsland.approxSize may
			 * become inaccurate, but impact would be small.
			 */
			biggerIsland.approxSize.incrementAndGet();
			graph.putIfAbsent(city, biggerIsland);
		} else {
			this.approxSize.incrementAndGet();
			graph.putIfAbsent(city, this);
			this.debugDisplayName.append("|"+city);
		}
	}

	public int getApproxSize() {
		return this.approxSize.get();
	}

	@Override
	public String toString() {
		return "{" + this.debugDisplayName + "[approxSize=" + getApproxSize() + "]}";
	}
}
