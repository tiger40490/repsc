package com.bgc;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.TreeSet;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Graph {
	static class Builder {
		private String fn;
		private String c1;
		private String c2;

		Builder withArray(String[] args) {
			if (args.length < 3)
				throw new IllegalArgumentException("Need 3 arguments");
			return this.withFileName(args[0]).withCityName1(args[1]).withCityName2(args[2]);
		}

		Builder withFileName(String s) {
			if (s == null || s.isEmpty())
				throw new IllegalArgumentException("invalid command line input");
			this.fn = s;
			return this;
		}

		Builder withCityName1(String s) {
			if (s == null || s.isEmpty())
				throw new IllegalArgumentException("invalid command line input");
			this.c1 = s;
			return this;
		}

		Builder withCityName2(String s) {
			if (s == null || s.isEmpty())
				throw new IllegalArgumentException("invalid command line input");
			this.c2 = s;
			return this;
		}

		Graph build() {
			Graph engine = new Graph(this.fn, this.c1, this.c2);
			return engine;
		}
	}// end of builder class

	public final String fileName, cityName1, cityName2;
	private final ConcurrentHashMap<String, Island> lookup = new ConcurrentHashMap<>();
	private final ReentrantReadWriteLock rwlock = new ReentrantReadWriteLock();
	private final Lock lookupReadLock = rwlock.readLock();
	private final Lock lookupWriteLock = rwlock.writeLock();

	// private constructor, Invoked by builder only
	private Graph(String s0, String s1, String s2) {
		this.fileName = s0;
		this.cityName1 = s1;
		this.cityName2 = s2;
		this.readTheFile();
	}

	private void readTheFile() {
		try (BufferedReader br = new BufferedReader(new FileReader(this.fileName))) {
			for (String line; (line = br.readLine()) != null;) {
				String[] tmp = line.replaceAll("\\s", "").split(",");
				if (tmp.length != 2)
					throw new IllegalStateException();
				this.read1pair(tmp[0], tmp[1]);
			}
			dumpLookupTable();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
	
	// no locking needed. Not needed in production.
	private void dumpLookupTable() {
		for (String city : new TreeSet<String>(this.lookup.keySet())) {
			System.out.println(city + " ->" + this.lookup.get(city) + "\t->..-> " 
					+ this.homeOf(city));
		}
		System.out.println(this.lookup.size() + "   cities in the universe");
	}

	/**
	 * look up to get the original island (if any) then follow the pointer to
	 * find the final answer
	 * 
	 * @return "final" island after redirections, or DummyIsland if the city is
	 *         new
	 */
	private Island homeOf(String city) {
		Island realRedirect = this.getOrDefault(city, Island.DUMMY_ISLAND);
		return realRedirect.realRedirect();
	}

	/* V0.8
	 * This method is currently called from constructor, i.e. single-threaded.
	 * 
	 * In the future this could run on multiple threads. See package-info.java.
	 */
	private void read1pair(String city1, String city2) {
		if (city1 == null || city1.isEmpty())
			throw new IllegalArgumentException();
		if (city2 == null || city2.isEmpty())
			throw new IllegalArgumentException();

		Island island1 = this.homeOf(city1);
		Island island2 = this.homeOf(city2);

		if (Island.DUMMY_ISLAND != island1 && island2 != Island.DUMMY_ISLAND) {
			/*
			 * both cities are known cities. Since we won't update lookup table,
			 * there's no need to lock it.
			 */
			if (island1 == island2)
				return; // nothing to update

			this.merge2islands(island1, island2);
			// no need to update lookup table
			return;
		}

		assert Island.DUMMY_ISLAND == island1 || island2 == Island.DUMMY_ISLAND; 
		// at least one newcomer
		
		lookupWriteLock.lock();//blocks all reader threads
		try {
			if (Island.DUMMY_ISLAND == island1 && island2 == Island.DUMMY_ISLAND) {
				// both newcomers
				Island newBornIsland = new Island(city1, city2);
				this.putIfAbsent(city1, newBornIsland);
				this.putIfAbsent(city2, newBornIsland);
				return;
			}
			// exactly one newcomer
			if (island1 == Island.DUMMY_ISLAND) { // city1 is newcomer
				island2.add(city1, this);
			} else {
				assert island2 == Island.DUMMY_ISLAND;
				island1.add(city2, this);
			}
		}finally{
			lookupWriteLock.unlock();
		}
	}

	/** V0.8
	 * The most challenging operation during {@link createIslands()}
	 * 
	 * Most important operation -- update the Island.mergedInto field.
	 * 
	 * No write to the global lookup table. No need for a global lock.
	 */
	private void merge2islands(Island AA, Island BB) {
		Island lock1, lock2;
		if (AA.id.compareTo(BB.id) < 0) {
			lock1 = AA;
			lock2 = BB;
		} else {
			assert AA.id.compareTo(BB.id) != 0 : "UUID are guaranteed unique!";
			lock1 = BB;
			lock2 = AA;
		}
		// Use a globally fixed locking order to prevent deadlock
		synchronized (lock1) {
			synchronized (lock2) {
				if (AA.isAcquired() || BB.isAcquired())
					return; // another thread already cleared AA or BB. No need
							// to merge

				if (AA.getApproxSize() <= BB.getApproxSize())
					// pick the smaller to wipe out -- efficiency
					AA.mergeInto(BB);
				else
					BB.mergeInto(AA);
			}
		}
	}

	/** V0.9
	 * No locking needed. This is a read-only method. It could give an answer
	 * based on out-dated information, but even with locking our answer could be
	 * out-dated.
	 */
	public boolean areConnected(String c_1111, String c_2222) {
		Island island1 = this.homeOf(c_1111);
		if (island1 == Island.DUMMY_ISLAND) {
			return false; // unknown city
		}

		Island island2 = this.homeOf(c_2222);
		// no need to check DUMMY_ISLAND. If indeed DUMMY_ISLAND, then surely
		// island1 != island2

		return island1 == island2;
	}

	/**
	 * This method is only used in main(), not for general use
	 */
	boolean checkTheConnection() {
		return this.areConnected(this.cityName1, this.cityName2);
	}

	private Island getOrDefault(String key, Island defaultValue) {
		lookupReadLock.lock();
		try {
			return this.lookup.getOrDefault(key, defaultValue);
		} finally {
			lookupReadLock.unlock();
		}
	}

	Island putIfAbsent(String key, Island value) {
		lookupWriteLock.lock();
		try {
			return this.lookup.putIfAbsent(key,value);
		} finally {
			lookupWriteLock.unlock();
		}
	}
}
