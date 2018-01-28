//$Id$
package com.hsbc.eventBus;

/**
 * @param <T> type of message
 */
public interface Predicate<T extends BaseMessage> {//v1.0
	@SuppressWarnings("unchecked")
	public final static Predicate DUMMY_FILTER_ALL_MESSAGE_TYPES = 
			new Predicate<BaseMessage>() {
		@Override
		public boolean isRelevant(BaseMessage message) {
			return true;
		}
	};
	boolean isRelevant(T message);
}
