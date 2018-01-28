//$Id$
package com.hsbc.eventBus;

import java.util.Date;

public class PriceMessage extends AbstractMessage {//v1.0
	private final String symbol;
	public final long priceInCents;
	private final boolean isConflating;
	public final Date timestamp = new Date();
	
	/**
	 * @param symbol
	 * @param price
	 * @param isConflating
	 */
	public PriceMessage(String symbol, long price, boolean isConflating) {
		if (null == symbol || symbol.isEmpty()) throw new IllegalArgumentException("invalid symbol");
		if (price <= 0) throw new IllegalArgumentException("price must be positive");
		this.symbol = symbol;
		this.priceInCents = price;
		this.isConflating = isConflating;
	}
	@Override
	public Date getTimestamp() {
		return timestamp;
	}

	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append(" PriceMessage [priceInCents=").append(this.priceInCents).append(
					", symbol=").append(this.symbol).append("]");
		return builder.toString();
	}
	@Override
	public String getSymbol() {
		return this.symbol;
	}
	@Override
	public boolean isConflating() {
		return this.isConflating;
	}
}
