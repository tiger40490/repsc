package com.hsbc.eventBus;

import java.util.Date;

interface BaseMessage { //v1.0
	Date getTimestamp();
	String getSymbol();
	
	/**If a Message (or PriceMessage or RateMessage..) has this flag
	 * set, then it will wipe out earlier messages under the same symbol.
	 */
	boolean isConflating();
}
public abstract class AbstractMessage implements BaseMessage{//v1
	/**
	 * Required by conflation. An incoming conflation 
	 * PriceMessage will wipe out all PriceMessage objects 
	 * equal to it.
	 * 
	 * @param o
	 * @return true if this.getSymbol() and o.getSymbol() match
	 */
	@Override
	final public boolean equals(Object o) {
		if (o == null) return false;
		if (!(o instanceof PriceMessage)) return false;
		if (o == this) return true;
		return ((PriceMessage) o).getSymbol().equals(this.getSymbol());
	}
	/**
	 * If 2 instances are "equal", then their hashCode must match
	 */
	@Override
	final public int hashCode() {
		return this.getSymbol().hashCode();
	}
}
