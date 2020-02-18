/* 
 * todo: efficiency improvement
 * todo: simplify data structures and everything else
 * showcase: linkedHashSet as dynamic sorted collection with O(1) remove but without insert. Not available in other languages.
 * showcase: as much as possible, all collections store integers rather than node references. Simplifies instrumentation greatly.
 * showcase: Arrays.asList(1,22,33)
 * Priority is time-efficiency of findPath(), not build1graph(). The latter is an one-time pre-processing.
 */
package com.lexdfs;

import java.util.*;
import java.util.Map.Entry;
public class PathFinder {
	public static void main(String[] args) {
		test2();
	}
	static void test0() {
		Graph inst = new Graph();
		inst.build1graph(Arrays.asList(11,22,33), Arrays.asList(22,33,11));
		inst.findPathFor1pair(33,11);		
	}
	static void test1() {
		Graph inst = new Graph();
		inst.build1graph(Arrays.asList(0,1,2,3), Arrays.asList(1,2,3,0));
		inst.findPathFor1pair(0,2);		
	}
	static void test2() {
		Graph inst = new Graph();
		inst.build1graph(Arrays.asList(0,3,1,0,1,2), Arrays.asList(3,4,2,1,3,4));
		//assert(1==inst.findPath1pair(0,1));		
		//assert(4==inst.findPath1pair(3,4));		
		//assert(4==inst.findPath1pair(2,4));		
		assert(4==inst.findPathFor1pair(1,2));		
	}
}
class Graph{
	final private HashSet<Integer> grey = new HashSet<>();
	void build1graph(List<Integer> end1, List<Integer> end2) {
		if (! Node.globalLookup.isEmpty()) return;
		assert(end1.size() == end2.size());
		for (int i=0; i<end1.size(); ++i) {
			final int idA = end1.get(i);
			final int idB = end2.get(i);
			Node nodeA, nodeB;
			if (Node.globalLookup.containsKey(idA)) {
				nodeA = Node.globalLookup.get(idA);
			}else {
				nodeA = new Node(idA);
			}
			if (Node.globalLookup.containsKey(idB)) {
				nodeB = Node.globalLookup.get(idB);
			}else {
				nodeB = new Node(idB);
			}
			nodeA.addNeighbor(idB);
			nodeB.addNeighbor(idA);
		}
	}
	/*
	 * Run one lexdfs cycle for one pair of start/target
	 */
	int findPathFor1pair(int start, int tgt) {
		for (Entry<Integer, Node> entry : Node.globalLookup.entrySet()) {
			final Node n = entry.getValue();
			n.edgeList = new LinkedHashSet<> (n.sortedView);
		}
		for (Entry<Integer, Node> entry : Node.globalLookup.entrySet()) {
			System.out.println(entry.getValue());
		}
		System.out.println("^^^ end of graph dump ^^^\n Now starting dfs from " + start + " -> " + tgt);
		assert (Node.globalLookup.containsKey(start));
		assert (Node.globalLookup.containsKey(tgt));
		int rank = lexdfs(start, tgt);
		System.out.println("findPath1pair() returning " + rank);
		return rank;
	}
	private int lexdfs(int cur, int tgt) {
		if (cur == tgt) {
			return 0;
		}
		grey.add(cur);
		System.out.println("entering lexdfs() with " + cur );
		
		Node node = Node.globalLookup.get(cur);
		assert (node != null);
		for (final int child: node.edgeList) {
			if (grey.contains(child)) {
				// child is already on the current stack i.e. an ancestor node
				continue;
			}
			int hopsFromTgt = lexdfs(child, tgt);
			if (hopsFromTgt >= 0) {
				System.out.println(hopsFromTgt + " : Node " + cur 
						+ " (possibly the start) is on the lucky pathway :)");				
				return hopsFromTgt +1;
			}
		}
		for (final int neighbor: node.edgeList) {
			System.out.println(cur + " (black node) removed as neighbor of" + neighbor);
			Node.globalLookup.get(neighbor).edgeList.remove(cur);
		}
		grey.remove(cur);
		return Integer.MIN_VALUE;
	}
}
class Node{
	public static final HashMap<Integer, Node> globalLookup=new HashMap<>();
	public final int id;
	private final TreeSet<Integer> internal = new TreeSet<>();
	public final SortedSet<Integer> sortedView = Collections.unmodifiableSortedSet(internal);
	public  LinkedHashSet<Integer> edgeList;
	public Node(int i) {
		this.id=i;
		Node.globalLookup.put(i, this);
	}
	public void addNeighbor(int i) {
		this.internal.add(i);
	}
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(id + ":");
		for (int i: this.edgeList) {
			sb.append(i + " ");
		}
		return sb.toString();
	}
}