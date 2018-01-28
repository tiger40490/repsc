//$Id$
package com.tanbinFIX.clientside.config;

public class ConfigServiceFactory {
	public enum ConfigType{
		TEST, UAT, PROD
	}
	public static IConfigService getConfigService(ConfigType type) {
		if (ConfigType.TEST == type) {
			return new TestConfigService();
		}
		throw new UnsupportedOperationException("");
	}
}
