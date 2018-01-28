package com.hsbc.slidingWindow;

public class LatencyMeasurement extends AbstractMeasurement {//v1.0

	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append("LatencyMeasurement [latencyInMillis=").append(
			this.latencyInMillis).append("]");
		return builder.toString();
	}
	private final int latencyInMillis; // could use float or long too

	public LatencyMeasurement(int i) {
		if (i <0) throw new IllegalArgumentException("latency input should be positive");
		this.latencyInMillis = i;
	}
	@Override
	public int intValue() {
		return this.latencyInMillis;
	}
}
