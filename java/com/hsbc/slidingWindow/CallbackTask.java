package com.hsbc.slidingWindow;

import java.util.concurrent.Callable;

public class CallbackTask implements Callable<Character> {// v1.0
	final public StatData msg;
	final public StatSubscriber sub;
	final public boolean isRelevant;

	/**
	 * @param msg
	 * @param sub
	 */
	public CallbackTask(StatData msg, StatSubscriber sub) {
		if (sub == null)
			throw new IllegalArgumentException("null subscriber");
		if (msg == null)
			throw new IllegalArgumentException("null stats");
		this.msg = msg;
		this.sub = sub;
		this.isRelevant = sub.isInterestedIn(msg);
	}

	@Override
	public Character call() throws Exception {
		if (!this.isRelevant)
			throw new IllegalStateException(
					"For irrelevant messages, task should"
							+ "not be created in the first place! Programmer error.");
		return this.sub.onMsg(this.msg);
	}
}
