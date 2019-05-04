package com.concretize;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.concurrent.ConcurrentLinkedQueue;

public class SpreadSheet {
	int num_rows = 0;
	int num_cols = 0;

	final public static Map<String, Cell> allCells = new LinkedHashMap<String, Cell>();
	/** precedent-to-dependents
	 */
	final private Map<SymbolicToken, Set<SymbolicToken>> p2d = new LinkedHashMap<SymbolicToken, Set<SymbolicToken>>();
	final private Queue<Cell> queue = new ConcurrentLinkedQueue<Cell>();

	public static void main(String[] args) throws Exception {
		SpreadSheet sheet = new SpreadSheet();
		sheet.makeSpreadsheetCells();
		while (!sheet.queue.isEmpty()) {
			sheet.dequeueOnce();
			out.println("after dequeue: " + sheet.queue);
		}
		if (sheet.p2d.isEmpty()) {
			out.println("all dependencies cleared:)");
		}else {
			err.println("Cyclic dependency found in " + sheet.p2d);
		}
	}

	private void dequeueOnce() { 
		Cell concretePreCell = queue.poll();
		SymbolicToken key = concretePreCell.rowColId;
		Set<SymbolicToken> dependents = p2d.remove(key);
		if (dependents == null) {
			dependents = Collections.emptySet();
		}
		System.out.println(concretePreCell.rowColId + " -p2d-> " + dependents);
		for (SymbolicToken tmp : dependents) {
			Cell depCell = allCells.get(tmp.rowColId);
			depCell.rpn.remove1precedent(key);
			if (depCell.isConcrete()) {
				enqueue(depCell);
			}
		}
	}

	private void enqueue(Cell cell) {
		if (!cell.isConcrete())
			throw new IllegalArgumentException();
		this.queue.add(cell);
		out.println("enqueued concrete cell - " + queue);
	}

	private void makeSpreadsheetCells() throws Exception {
		String tmp[] = null;
		int total_SpreadsheetCells = 0;
		char rowId;
		int colId;

		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String s;

		System.out
				.println("Pleae enter your spreadsheet (using predefined format): ");

		// Due to time constraint, I will not do any input validation here.
		// I assume the user will input the data correctly.

		// TODO: Should do validation. But skipping for now due to time
		// constraint.
		s = in.readLine();
		tmp = s.split(" ");
		num_cols = Integer.parseInt(tmp[0]);
		num_rows = Integer.parseInt(tmp[1]);
		total_SpreadsheetCells = num_rows * num_cols;

		rowId = 'A';
		for (int i = 0; i < total_SpreadsheetCells; i++) {
			// final SpreadsheetCell cell = new SpreadsheetCell();
			// TODO: Should do validation. But skipping for now due to time
			// constraint.
			s = in.readLine().replaceAll("\\\\n", "");

			colId = (i + 1) % num_cols;
			colId = colId == 0 ? num_cols : colId;
			Cell c = new Cell(s, "" + rowId + colId);
			if (c.rpn.isConcrete()) {
				enqueue(c);
			}
			allCells.put(c.rowColId.toString(), c);

			for (SymbolicToken precedent : c.rpn.precedents) {
				Set<SymbolicToken> dependentS = p2d.get(precedent);
				if (dependentS == null) {
					dependentS = new LinkedHashSet<SymbolicToken>();
					p2d.put(precedent, dependentS);
				}
				dependentS.add(c.rowColId);
			}

			if (colId == num_cols) {
				rowId++;
				// The question said
				// "you can assume there are no more than 26 rows (A-Z)",
				// so here I just use "++" to get the next row ID without
				// doing any validation.
			}
		}

		System.out.println("v v v -- The spreadsheet you entered is as follows -- v v v");
		// Print out to check if we have got the input correctly
		System.out.println(allCells.values() + "");
		System.out.println("Precedent/Dependencies pairs: " + p2d);
		System.out.println("^ ^  ^ ^ ^ ^ ^ ^");
	}
}