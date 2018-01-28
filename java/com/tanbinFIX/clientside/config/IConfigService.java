//$Id$
package com.tanbinFIX.clientside.config;

public interface IConfigService {

	/**
	 * how long to sleep between sending messages. testing only
	 * 
	 * @return
	 */
	public int getSleepMillsForTesting();
	public String getServerHostName();

	public long getSilenceThreshold();

	public int getCheckInterval();

	public int getHeartBeatIntervalMills();

}
