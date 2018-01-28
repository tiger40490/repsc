package com.xx.garbagecollector;

import static java.lang.System.out;

import java.lang.management.GarbageCollectorMXBean;
import java.lang.management.ManagementFactory;
import java.lang.management.MemoryMXBean;
import java.lang.management.MemoryPoolMXBean;
import java.lang.management.MemoryUsage;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Formatter;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

// ----------------------------------------------------------------------------
/**
 * @author <a href="mailto:vlad@trilogy.com">Vladimir Roubtsov</a>, modified by
 *         TAN,Bin
 */
class Sizeof {

	// this is our way of requesting garbage collection to be run:
	// [how aggressive it is depends on the JVM to a large degree, but
	// it is almost always better than a single Runtime.gc() call]
	static public void runGC() {
		// for whatever reason it helps to call Runtime.gc()
		// using several method calls:
		for (int r = 0; r < 4; ++r)
			_runGC();
	}

	static public StringBuilder printHeapSegments4JDK6() {
		final StringBuilder ret = new StringBuilder();
		final Formatter formatter = new Formatter(ret);
		final List<GarbageCollectorMXBean> gcMBeans = ManagementFactory
				.getGarbageCollectorMXBeans();
		for (GarbageCollectorMXBean collector : gcMBeans) {
			final long justRan = justRan(collector);
			if (justRan > 0) {
				formatter.format(
						"    ^ ^ %16s collector ran %d/%d time(s) and covers "
								+ Arrays.toString(collector
										.getMemoryPoolNames()) + "\n",
						collector.getName(), justRan, collector
								.getCollectionCount());
			}
		}

		final MemoryMXBean memMXBean = ManagementFactory.getMemoryMXBean();
		memMXBean.setVerbose(true); // not sure how useful
		MemoryUsage heap = memMXBean.getHeapMemoryUsage();
		ret.append(heap.toString() + "\n");

		MemoryUsage nonHeap = memMXBean.getNonHeapMemoryUsage();
		ret.append(nonHeap.toString() + "\n");

		List<MemoryPoolMXBean> pool = ManagementFactory.getMemoryPoolMXBeans();
		for (int i = 0; i < pool.size(); i++) {
			MemoryPoolMXBean bean = pool.get(i);
			ret.append(bean.getName() + "\t");
			ret.append(bean.getType() + "\t");
			ret.append(bean.getUsage() + "\n");
		}
		System.out.println(ret);
		return ret;
	}

	private static long justRan(GarbageCollectorMXBean collector) {
		final Long newCount = collector.getCollectionCount();
		if (newCount <= 0)
			return 0;
		Long oldCount = collectionCounts.put(collector, newCount);
		if (oldCount == null)
			return newCount;
		long ret = newCount - oldCount;
		return ret > 0 ? ret : 0;
	}

	private static ConcurrentHashMap<GarbageCollectorMXBean, Long> collectionCounts = new ConcurrentHashMap<GarbageCollectorMXBean, Long>();

	static private void _runGC() {
		long usedMem1 = used(), usedMem2 = Long.MAX_VALUE;
		for (int i = 0; (usedMem1 < usedMem2) && (i < 1000); ++i) {
			s_runtime.runFinalization();
			s_runtime.gc();
			Thread.yield();
			usedMem2 = usedMem1;
			usedMem1 = used();
		}
	}

	static public long used() {
		return s_runtime.totalMemory() - s_runtime.freeMemory();
	}

	static public long total_ie_Committed() {
		return s_runtime.totalMemory();
	}

	static private final Runtime s_runtime = Runtime.getRuntime();
} // end of class
// ----------------------------------------------------------------------------
public class GcDemo {
	static ArrayList<byte[]> list = new ArrayList<byte[]>();
	public static void main(String[] kkkj) throws InterruptedException {
		byte[] array = null;
		for (;;) {
			Sizeof.printHeapSegments4JDK6();
			out.println(Sizeof.total_ie_Committed() + "\t>  " + Sizeof.used()
					+ " <-- bytes in use. Trying to new up....");
			try {
				array = new byte[20 * 1000 * 1000];
			} catch (OutOfMemoryError e) {
				StringBuilder stat = Sizeof.printHeapSegments4JDK6();
				System.err.println(stat);
				e.printStackTrace();
			}
			list.add(array);
		}
	}
}