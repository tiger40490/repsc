package com.lexdfs;

import java.util.*;
import java.util.Map.Entry;
/* todo: more tests
 * todo: efficiency improvement
 * showcase: as much as possible, all collections store integers rather than node references
 * Priority is time-efficiency of findPath(), not build1graph()
 */
public class PathFinder {
	public static void main(String[] args) {
		Graph inst = new Graph();
		inst.build1graph(Arrays.asList(11,22,33), Arrays.asList(22,33,11));
		inst.findPath1pair(33,22);
	}
}
class Graph{
	final private HashSet<Integer> grey = new HashSet<>();
	void build1graph(List<Integer> end1, List<Integer> end2) {
		assert(end1.size() == end2.size());
		for (int i=0; i<end1.size(); ++i) {
			final int idA = end1.get(i);
			final int idB = end2.get(i);
			GraphNode nodeA, nodeB;
			if (GraphNode.globalLookup.containsKey(idA)) {
				nodeA = GraphNode.globalLookup.get(idA);
			}else {
				nodeA = new GraphNode(idA);
			}
			if (GraphNode.globalLookup.containsKey(idB)) {
				nodeB = GraphNode.globalLookup.get(idB);
			}else {
				nodeB = new GraphNode(idB);
			}
			nodeA.addNeighbor(idB);
			nodeB.addNeighbor(idA);
		}
	}
	/*
	 * Run one lexdfs cycle for one pair of start/target
	 */
	int findPath1pair(int start, int tgt) {
		for (Entry<Integer, GraphNode> entry : GraphNode.globalLookup.entrySet()) {
			final GraphNode n = entry.getValue();
			n.edgeList = new LinkedHashSet<> (n.sortedList);
		}
		for (Entry<Integer, GraphNode> entry : GraphNode.globalLookup.entrySet()) {
			System.out.println(entry.getValue());
		}
		System.out.println("^^^ end of graph dump ^^^\n Now starting dfs from " + start + " -> " + tgt);
		assert (GraphNode.globalLookup.containsKey(start));
		assert (GraphNode.globalLookup.containsKey(tgt));
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
		
		GraphNode node = GraphNode.globalLookup.get(cur);
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
			GraphNode.globalLookup.get(neighbor).edgeList.remove(cur);
		}
		grey.remove(cur);
		return Integer.MIN_VALUE;
	}
}
class GraphNode{
	public static final HashMap<Integer, GraphNode> globalLookup=new HashMap<>();
	public final int id;
	private final TreeSet<Integer> internal = new TreeSet<>();
	public final SortedSet<Integer> sortedList = Collections.unmodifiableSortedSet(internal);
	public  LinkedHashSet<Integer> edgeList;
	public GraphNode(int i) {
		this.id=i;
		GraphNode.globalLookup.put(i, this);
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