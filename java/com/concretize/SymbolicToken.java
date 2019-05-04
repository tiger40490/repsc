package com.concretize;

/** A special type of token in a formula. A Symbolic token is not a number and not an operator.
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
