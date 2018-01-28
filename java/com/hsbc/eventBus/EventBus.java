package com.hsbc.eventBus;

public interface EventBus<T extends BaseMessage> { //v1.0
	// Feel free to replace Object with something more specific,
	// but be prepared to justify it
	void publishEvent(T m);

	// How would you denote the subscriber?
	/**
	 * This method will use messgeType to look up the message queue and register
	 * the subscriber on that queue.
	 * 
	 * New subscriber will immediately start receiving subsequent (not historical) 
	 * messages published to this message queue.
	 */
	void addSubscriber(Class<T> messageType, Subscriber<T> sub);
	
	// Would you allow clients to filter the events they receive? How would the
	// interface look like?
	/**See package-info.java about the dispatcher and tasks.
	 * 
	 * In this implementation, the predicate (i.e. filter condition) is a 
	 * required field of the subscriber, so the addSubscriber() method can 
	 * do everything and this method is unnecessary. 
	 * If a subscriber containing a predicate is already created, you can 
	 * pass it to either this or addSubscriber() method.
	 */
	void addSubscriberForFilteredEvents(Class<T> messageType, 
			Subscriber<T> sub);

}

