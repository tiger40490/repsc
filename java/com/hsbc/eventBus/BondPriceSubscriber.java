package com.hsbc.eventBus;

public class BondPriceSubscriber implements Subscriber<BondPriceMessage>{//v0.9
	final public Predicate<BondPriceMessage> pred;
	final public char id=89;
	
	@SuppressWarnings("unchecked")
	public  BondPriceSubscriber() {
		this(Predicate.DUMMY_FILTER_ALL_MESSAGE_TYPES); 
		//this filter returns true every time.
	}
	public BondPriceSubscriber(Predicate<BondPriceMessage> pred) {
		if (pred == null)
			throw new IllegalArgumentException("null predicate");
		this.pred = pred;		
	}
	@Override
	public char onMsg(BondPriceMessage msg) {
		System.out.println("[Thread # "
			+ Thread.currentThread().getId()
			+ " ] BondPriceSubscriber.onMsg() <-- " + this + msg);
		return '0';
	}
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append(" Subscriber#").append(this.id);
		return builder.toString();
	}
	@Override
	public boolean isInterestedIn(BondPriceMessage msg) {
		return this.pred.isRelevant(msg);
	}
}