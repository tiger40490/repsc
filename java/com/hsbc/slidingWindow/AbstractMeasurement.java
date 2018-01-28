package com.hsbc.slidingWindow;

public abstract class AbstractMeasurement implements Measurement {//v1.0

	@Override
	public double floatValue() {
		throw new UnsupportedOperationException("this method isn't supported in this measurmeent");
	}

	@Override
	public int intValue() {
		throw new UnsupportedOperationException("this method isn't supported in this measurmeent");
	}

}
