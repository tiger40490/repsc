package com.gelber;

import java.io.IOException;
import java.io.LineNumberReader;
import java.io.Reader;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MultiCounter implements Serializable{
	private static final long serialVersionUID = -1521271866887124929L;
	static MultiCounter instance = new MultiCounter();

	private static void add1(
			ConcurrentHashMap<String, ConcurrentMutableInteger> map, String s) {
		assert s != null && map != null;
		map.putIfAbsent(s, new ConcurrentMutableInteger());
		map.get(s).increment();
	}

	public static void mainTest(String[] asjl) {
		MultiCounter inst = new MultiCounter();
		String aLine = "aa <meta > 12bb\n 12bb23 add <meta > aa  33 cc";
		String kk = aLine.replaceAll("(?s)<meta .*?>", "");
		System.out.println(kk);
		inst.processLine(aLine);
		inst.dumpCounts();
	}

	private static void printTopN(Map<String, ConcurrentMutableInteger> map,
			int topN) {
		List<NumStringPair> list = new ArrayList<NumStringPair>(map.size());
		for (String s : map.keySet()) {
			int occurence = map.get(s).getInt();
			list.add(new NumStringPair(occurence, s));
		}
		// sort by occurence, from most common to least
		Collections.sort(list);
		int i = 0;
		System.out.print("Top " + topN + " -- ");
		for (NumStringPair p : list) {
			System.out.print(p);
			if (++i >= topN)
				break;
		}
		System.out.println();
	}

	private final Pattern charPattern = Pattern.compile("(.)");
	public final ConcurrentHashMap<String, ConcurrentMutableInteger> letterCount = new ConcurrentHashMap<String, ConcurrentMutableInteger>(
			26 * 2);
	public final ConcurrentHashMap<String, ConcurrentMutableInteger> nonLetterCount = new ConcurrentHashMap<String, ConcurrentMutableInteger>(
			256);
	public final ConcurrentHashMap<String, ConcurrentMutableInteger> numCount = new ConcurrentHashMap<String, ConcurrentMutableInteger>(
			999);

	// a string of digits without dot or comma
	private final Pattern numPattern = Pattern.compile("(\\d+)");

	private final Pattern whiteSpace = Pattern.compile("\\s");

	/**
	 * A WORD is a string of non-space characters
	 */
	public final ConcurrentHashMap<String, ConcurrentMutableInteger> wordCount = new ConcurrentHashMap<String, ConcurrentMutableInteger>(
			999);

	void dumpCounts() {
		System.out.println("--Words--\n" + wordCount);
		printTopN(wordCount, 2);

		System.out.println("--Numbers--\n" + numCount);
		printTopN(numCount, 2);

		System.out.println("--Letters--\n" + letterCount);
		printTopN(letterCount, 2);

		Map<String, ConcurrentMutableInteger> charCount = new ConcurrentHashMap<String, ConcurrentMutableInteger>(
				nonLetterCount);
		charCount.putAll(letterCount);
		System.out.println("--Chars--\n" + charCount);
		printTopN(charCount, 2);
	}

	public void processFile(Reader is, boolean stripMeta) {
		LineNumberReader reader = new LineNumberReader(is);
		String line;
		StringBuffer everything = new StringBuffer();
		try {
			while ((line = reader.readLine()) != null) {
				if (stripMeta) {
					everything.append(line + "\n");
				} else {
					this.processLine(line);
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		if (stripMeta) {
			String clean = everything.toString().replaceAll("(?s)<meta .*?>",
					"");
			System.out.println("HTML stripped of " + (everything.length() - clean.length()) + " characters");
			this.processLine(clean);
		}
	}

	private void processLine(String aLine) {
		for (String word : aLine.split("\\s+")) {
			this.processWord(word);
		}
	}

	/**
	 * update the various counters
	 * 
	 * @param s
	 */
	private void processWord(String s) {
		assert s != null : "input string is null";
		assert !whiteSpace.matcher(s).find() : "incoming word should not contain spaces!";
		if (s.length() == 0) {
			return;
		}
		add1(wordCount, s);
		Matcher mat = numPattern.matcher(s);
		while (mat.find()) {
			add1(numCount, mat.group(1));
		}
		mat = charPattern.matcher(s);
		while (mat.find()) {
			String aChar = mat.group(1);
			char capitalized = aChar.toUpperCase().charAt(0);
			if ('A' <= capitalized && capitalized <= 'Z') {
				add1(letterCount, aChar);
			} else {
				add1(nonLetterCount, aChar);
			}
		}

	}
}
