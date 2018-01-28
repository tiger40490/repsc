//$Id$
package com.tanbinFIX.clientside.config;


public class TestConfigService implements IConfigService {
	String serverHostName;

	/**
	 * 
	 set up configurations useing the config file;
	 * 
	 * @param configFile
	 */
	public TestConfigService(String configFile) {
		this.serverHostName = "localhost";
	}

	public TestConfigService() {
		this("TestConfig.txt, but ignored in this test");
	}

	@Override
	public String getServerHostName() {
		return this.serverHostName;
	}

	/**
	 * in mills
	 */
	@Override
	public long getSilenceThreshold() {
		return 500; //500 would trigger Destroyer to detect a long silence without heart beat, and close everything
	}

	@Override
	public int getCheckInterval() {
		return 1500; //
	}

	@Override
	public int getHeartBeatIntervalMills() {
		return 700;
	}

	@Override
	public int getSleepMillsForTesting() {
		return 2000;
	}
}
