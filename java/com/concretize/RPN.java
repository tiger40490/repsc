//$Id$
package com.concretize;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

/**
 * This class doesn't use cells or spredsheets. The precedents can be any
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

	public static double evalRPN(String... originalInput) {
		return new RPN(originalInput).numericResult();
	}

	public static void main(String[] args) {
		RPN inst = new RPN("5.1 3 4 - *");
		System.out.println(inst.isConcrete());
		System.out.println(inst.result);
	}

	private boolean isFullyConcretized = false;
	private final Set<SymbolicToken> _symbolicTokens = new HashSet<SymbolicToken>();
	public final Set<SymbolicToken> precedents = Collections
			.unmodifiableSet(_symbolicTokens);
	private double result = Double.MIN_VALUE;
	private final ArrayList<String> tokens;

	public RPN(Collection<String> originalInput) {
		this.tokens = new ArrayList<String>(originalInput);
		for (String e : tokens) {
			e = e.trim().toUpperCase();
			try {
				Double.parseDouble(e);
			} catch (NumberFormatException ex) {
				if (!"+-*/".contains(e))
					_symbolicTokens.add(new SymbolicToken(e));
			}
		}
		tryConcretizeRPN();
	}

	public RPN(String s) {
		this(s.split("\\s+"));
	}

	public RPN(String... originalInput) {
		this(Arrays.asList(originalInput));
	}

	@Override
	public String toString() {
		String ret = tokens + "";
		if (isConcrete())
			ret += "===" + numericResult();
		return ret;
	}

	/**
	 * look for precedent in tokens. If found, replace it with value.
	 * 
	 * If possible, calculate result and set isFullyConcretized.
	 * 
	 * @param precedent
	 * @param value
	 */
	public void concretize1precedent(SymbolicToken precedent, double value) {
		if (isFullyConcretized)
			return;
		if (this._symbolicTokens.contains(precedent)) {
			for (int i = 0; i < tokens.size(); ++i) {
				if (tokens.get(i).equals(precedent.key))
					tokens.set(i, value + "");
			}
			_symbolicTokens.remove(precedent);
			tryConcretizeRPN();
		}
	}

	public double numericResult() {
		if (!isConcrete())
			throw new IllegalStateException();
		return result;
	}

	public boolean isConcrete() {
		return this.isFullyConcretized;
	}

	private void tryConcretizeRPN() {
		if (isFullyConcretized)
			return;
		if (_symbolicTokens.isEmpty()) {
			StringBuilder sb = new StringBuilder();
			for (String s : tokens) {
				sb.append(s);
				sb.append(" ");
			}
			result = evalRPN(sb.toString());
			isFullyConcretized = true;
		}
	}
}