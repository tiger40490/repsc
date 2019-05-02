//$Id$
package com.concretize;

public class SymbolicToken {// SymbolicToken
	public final String key;

	public SymbolicToken(String k) {
		if (k==null || k.isEmpty()) throw new IllegalArgumentException();
		this.key = k;
	}

	@Override
	public String toString() {
		return key;
	}

	@Override
	public boolean equals(Object o) {
		if (!o.getClass().equals(getClass())) return false;
		return key.equals(o.toString());
	}

	@Override
	public int hashCode() {
		return key.hashCode();
	}
}
