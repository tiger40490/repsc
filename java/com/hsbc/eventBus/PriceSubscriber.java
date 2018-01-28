//$Id$
package com.hsbc.eventBus;

public class PriceSubscriber implements Subscriber<PriceMessage>{
	final public Predicate<PriceMessage> pred;
	final public char id;
	public  PriceSubscriber() {
		this('0');
	}
	@SuppressWarnings("unchecked")
	public PriceSubscriber(char id) {
		this(id, Predicate.DUMMY_FILTER_ALL_MESSAGE_TYPES); //this filter returns true every time.
	}
	public PriceSubscriber(char id, Predicate<PriceMessage> pred) {
		if (pred == null)
			throw new IllegalArgumentException("null predicate");
		this.pred = pred;		
		this.id = id;
	}
	@Override
	public char onMsg(PriceMessage msg) {
		System.out.println("[Thread # "
			+ Thread.currentThread().getId()
			+ " ] PriceSubscriber.onMsg() <-- " + this + msg);
		return '0';
	}
	@Override
	public boolean isInterestedIn(PriceMessage msg) {
		return this.pred.isRelevant(msg);
	}
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append(" Subscriber#").append(this.id);
		return builder.toString();
	}
}