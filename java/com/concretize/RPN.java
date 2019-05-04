package com.concretize;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

/**
 * This class doesn't use cells or spreadsheets. The precedents can be any
 * symbolic name that evaluates to a numeric value.
 */
public class RPN {
	public static double evalRPN(String expr) {
		String cleanExpr = expr.replaceAll("[^\\*\\+\\-\\d/\\s\\.]", "");
		LinkedList<Double> stack = new LinkedList<Double>();
		// System.out.println("Input\tOperation\tStack after");
		for (String token : cleanExpr.split("\\s")) {
			// System.out.print(token + "\t");
			Double tokenNum = null;
			try {
				tokenNum = Double.parseDouble(token);
			} catch (NumberFormatException e) {
			}
			if (tokenNum != null) {
				// System.out.print("Push\t\t");
				stack.push(Double.parseDouble(token + ""));
			} else if (token.equals("*")) {
				// System.out.print("Operate\t\t");
				double secondOperand = stack.pop();
				double firstOperand = stack.pop();
				stack.push(firstOperand * secondOperand);
			} else if (token.equals("/")) {
				// System.out.print("Operate\t\t");
				double secondOperand = stack.pop();
				double firstOperand = stack.pop();
				stack.push(firstOperand / secondOperand);
			} else if (token.equals("-")) {
				// System.out.print("Operate\t\t");
				double secondOperand = stack.pop();
				double firstOperand = stack.pop();
				stack.push(firstOperand - secondOperand);
			} else if (token.equals("+")) {
				// System.out.print("Operate\t\t");
				double secondOperand = stack.pop();
				double firstOperand = stack.pop();
				stack.push(firstOperand + secondOperand);
			} else {
				throw new IllegalArgumentException();
			}
			// System.out.println(stack);
		}
		double ret = stack.pop();
		// System.out.println("result = " + ret);
		return ret;
	}

	public static void main(String[] args) {
		RPN inst = new RPN("5.1 3 4 - *");
		System.out.println(inst.isConcrete());
		System.out.println(inst._result);
	}

	private boolean _isFullyConcretized = false;
	private final Set<SymbolicToken> _d2p = new HashSet<SymbolicToken>();
	public final Set<SymbolicToken> precedents = 
			Collections.unmodifiableSet(_d2p);
	private double _result = Double.MIN_VALUE;
	
	/**the sequence of tokens in the original formula. May contain 
	 * the same precedent multiple times.
	 */
	private final String[] _tokens;

	public RPN(String formula) {
		this._tokens = formula.split("\\s+");
		for (String e : _tokens) {
			e = e.trim().toUpperCase();
			if (SymbolicToken. isRef(e)) {
				_d2p.add(new SymbolicToken(e));
			}
		}
		tryConcretizeRPN();
	}

	@Override
	public String toString() {
		String ret = Arrays.toString(_tokens).intern(); //inefficient if called frequently
		if (isConcrete()) ret += " = " + numericResult();
		return ret;
	}

	public void remove1precedent(SymbolicToken precedent) {
		if (_isFullyConcretized) return;
		_d2p.remove(precedent);
		if (_d2p.isEmpty()) tryConcretizeRPN();
	}

	public double numericResult() {
		if (!isConcrete()) throw new IllegalStateException();
		return _result;
	}

	public boolean isConcrete() {
		return this._isFullyConcretized;
	}

	private void tryConcretizeRPN() {
		if (_isFullyConcretized) return;
		if (_d2p.isEmpty()) {
			StringBuilder sb = new StringBuilder();
			for (String s : _tokens) {				
				if (SymbolicToken.isRef(s)) {
					sb.append("" + SpreadSheet.allCells.get(s).rpn.numericResult());
				}else {
				    sb.append(s);
				}
				sb.append(" ");
			}
			_result = evalRPN(sb.toString());
			_isFullyConcretized = true;
		}
	}
}