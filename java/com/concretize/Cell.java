//$Id$
package com.concretize;



public class Cell {
	public String key;
	public RPN rpn;

	public static void main(String[] asdfa) {
		Cell inst = new Cell("5 A3 4 - *", "A2");
		if (inst.rpn.isConcrete()) {
			System.out.println("cell value = " + inst.rpn.numericResult());
		}
	}

	public Cell(String expression, String name) {
		name = name.trim().toUpperCase();
		if (name.length() != 2)
			throw new IllegalArgumentException();
		this.key = name;
		this.rpn = new RPN(expression);
	}

	@Override
	public String toString() {
		String ret = key + "{"+ rpn + "}";
		return ret;
	}

	public boolean isConcrete() {
		return rpn.isConcrete();
	}
}
