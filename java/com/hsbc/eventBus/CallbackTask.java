package com.hsbc.eventBus;

import java.util.concurrent.Callable;

public class CallbackTask<T extends BaseMessage> implements Callable<Character> {// v1.0
	final public T msg;
	final public Subscriber<T> sub;
	final public boolean isRelevant;

	@SuppressWarnings("unchecked")
	public static CallbackTask<? extends BaseMessage> create(BaseMessage msg,
			Subscriber<? extends BaseMessage> sub) {
		return new CallbackTask(msg,  sub);
	}

	/** 
	 * @param msg
	 * @param sub
	 */
	public CallbackTask(T msg, Subscriber<T> sub) {
		if (sub == null)
			throw new IllegalArgumentException("null subscriber");
		if (msg == null)
			throw new IllegalArgumentException("null msg");
		this.msg = msg;
		this.sub = sub;
		this.isRelevant = sub.isInterestedIn(msg);
	}

	@Override
	public Character call() throws Exception {
		if (!this.isRelevant)
			throw new IllegalStateException(
					"For irrelevant messages, task should"
							+ "not be created! Programmer error.");
		return this.sub.onMsg(this.msg);
	}

}
