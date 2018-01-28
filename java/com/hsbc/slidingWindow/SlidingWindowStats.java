package com.hsbc.slidingWindow;

public interface SlidingWindowStats <T extends Measurement>{//v1.0

	void add(T measurement);

    // subscriber will have a callback that'll deliver a Statistics instance (push)
    void subscribeForStatistics(StatSubscriber sub);

    Statistics getLatestStatistics();

	void clearAll();

	public interface Statistics {
        double getMean();
        
        /**
         * if 2 values both have the highest frequency, then the smaller  
         * is returned.
         * 
         */
        double getMode();
        
        /**See https://en.wikipedia.org/wiki/Percentile#The_Nearest_Rank_method
         * 
         * @param rank must be 1 or 2 or 3 .. up to 100.
         * @return the Nth percentile value
         */
        double getPctile(int rank);
    }

}
