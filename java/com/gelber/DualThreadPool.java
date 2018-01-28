package com.gelber;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
public class DualThreadPool {
	/**
	 * Construct a thread pool (size 2) with an internal queue holding tasks 
	 */
	private final ExecutorService eService = Executors.newFixedThreadPool(2);
	private void addTask(Callable<String> task) {
		assert task != null;
		this.eService.submit(task);
	}
	public static void main(String adfs32[]) throws FileNotFoundException, InterruptedException {
		DualThreadPool pool = new DualThreadPool();
		pool.addTask(new FileParserTask(Downloader.download("www.gs.com", ""), true));
		pool.addTask(new FileParserTask(Downloader.download("www.2wire.com", ""), true));
		pool.addTask(new FileParserTask(Downloader.download("www.google.com", ""), true));
		pool.addTask(new FileParserTask(new FileReader("c:/windows/ie7.log")));
		pool.addTask(new FileParserTask(new FileReader("c:/windows/ie7_main.log")));
		pool.addTask(new FileParserTask(new FileReader("c:/windows/ie8_main.log")));
		pool.addTask(new FileParserTask(new FileReader("c:/windows/iis6.log")));
		pool.eService.shutdown();
		pool.eService.awaitTermination(22, TimeUnit.SECONDS);
		MultiCounter.instance.dumpCounts();
	}
}
