package com.hsbc.slidingWindow;

public class StatSubscriber {//v1.0
	final public Predicate pred;
	final public char id;

	public StatSubscriber(char id) {
		this(id, Predicate.DUMMY_FILTER_ALL_MESSAGE_TYPES); //this filter returns true every time.
	}
	public StatSubscriber(char id, Predicate pred) {
		if (pred == null)
			throw new IllegalArgumentException("null predicate");
		this.pred = pred;		
		this.id = id;
	}
	public char onMsg(StatData msg) {
		System.out.println("[Thread # "
			+ Thread.currentThread().getId()
			+ " ] onMsg() <--" + this + msg);
		return '0';
	}
	public boolean isInterestedIn(StatData msg) {
		return this.pred.isRelevant(msg);
	}
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append(" Subscriber#").append(this.id);
		return builder.toString();
	}
}
