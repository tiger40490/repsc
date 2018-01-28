package com.hsbc.slidingWindow;

public interface Predicate {//v1.0
	public final static Predicate DUMMY_FILTER_ALL_MESSAGE_TYPES = 
			new Predicate() {
		@Override
		public boolean isRelevant(StatData message) {
			return true;
		}
	};
	boolean isRelevant(StatData message);
}
