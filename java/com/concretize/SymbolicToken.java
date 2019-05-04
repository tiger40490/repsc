package com.concretize;

/**
 * Meaning of a SymbolicToken -- A special type of token in a formula. A Symbolic token 
 * is not a number and not an operator.
 * 
 * Q: Why this wrapper class over String.java?  
 * 1) This wrapper provides string validation since the input data may have typos like A_2 or BB3
 * 2) isRef() function is needed beyond validation
 * 
 * Q: When is String.java a simpler and cheaper alternative?
 * When I generate the strings such as the keys to allCells.
 */
public class SymbolicToken {
	static public boolean isRef(String token) {
		char c = token.charAt(0);
		return ('A'<=c && c<='Z' );
	}
	public final String rowColId;

	public SymbolicToken(String k) {
		if (k==null || k.length()<2 || !isRef(k)) throw new IllegalArgumentException();
		this.rowColId = k;
	}

	@Override
	public String toString() {
		return rowColId;
	}

	@Override
	public boolean equals(Object o) {
		if (!o.getClass().equals(getClass())) return false;
		return rowColId.equals(o.toString());
	}

	@Override
	public int hashCode() {
		return rowColId.hashCode();
	}
}
