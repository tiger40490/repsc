package com.gelber;

import java.io.Reader;
import java.util.concurrent.Callable;

public class FileParserTask  implements Callable<String> {
	private final Reader reader;
	private final boolean stripMeta ;
	
	FileParserTask(Reader r, boolean stripMetaTags) {
		assert r!=null;
		this.reader = r;
		this.stripMeta = stripMetaTags;
	}
	FileParserTask(Reader r) {
		this(r,false);
	}
	@Override
	public String call() throws Exception {
		MultiCounter.instance.processFile(this.reader, this.stripMeta);
		return "0"; // 0 means good.
	}
}
