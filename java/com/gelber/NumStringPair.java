package com.gelber;

/**
 * Like the STL pair class. Holds a string and a count.
 * 
 * Used for sorting based on the numeric field.
 *
 */
public class NumStringPair implements Comparable<NumStringPair>{
	private final int occurence;
	private final String str;
	
	NumStringPair(int _occurence, String _string) {
		this.occurence = _occurence;
		this.str = _string;
	}
	@Override
	public int compareTo(NumStringPair other) {
		return other.occurence - this.occurence;
		
	}
	@Override
	public String toString() {
		return this.str+"("+this.occurence+") ";
	}
}
