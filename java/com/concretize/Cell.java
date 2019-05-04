package com.concretize;

public class Cell {
	public final SymbolicToken rowColId;
	public final RPN rpn;

	public static void main(String[] asdfa) {
		Cell inst = new Cell("5 A3 4 - *", "A2");
		if (inst.rpn.isConcrete()) {
			System.out.println("cell value = " + inst.rpn.numericResult());
		}
	}

	public Cell(String expression, String rcid) {
		rcid = rcid.trim().toUpperCase();
		if (rcid.length() < 2)
			throw new IllegalArgumentException();
		this.rowColId = new SymbolicToken(rcid);
		this.rpn = new RPN(expression);
	}

	@Override
	public String toString() {
		return rowColId + "{"+ rpn + "}";
	}

	public boolean isConcrete() {
		return rpn.isConcrete();
	}
}
