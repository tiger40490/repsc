//$Id$
package com.hsbc.eventBus;

/**This is a parametrized Subscriber. For example, A 
 * Subscriber<PriceMessage> would only process PriceMessage.
 * 
 * @param <T> type of message for this subscriber. 
 */
interface Subscriber<T extends BaseMessage> {//v1.0
	/**
	 * @return a status code, for future use
	 */
	char onMsg(T msg);
	boolean isInterestedIn(T msg);
}