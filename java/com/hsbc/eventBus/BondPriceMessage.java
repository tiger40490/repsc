//$Id$
package com.hsbc.eventBus;

public class BondPriceMessage extends PriceMessage {// v1.0
	final double bondYield;

	public BondPriceMessage(String symbol, long price, boolean isCoalescing,
			double yield) {
		super(symbol, price, isCoalescing);
		if (yield <=0) throw new IllegalArgumentException("yield must be positive");
		this.bondYield = yield;
	}

	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append(" BondPriceMessage [yield=").append(this.bondYield)
				.append(", priceInCents=").append(this.priceInCents).append(
					", Symbol=").append(this.getSymbol()).append("]");
		return builder.toString();
	}
}
