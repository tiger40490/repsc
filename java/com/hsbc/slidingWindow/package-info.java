/** 
 * Design is based on EventBus project, with changes to concurrent data structure
 * 
 * A concurrent queue will be used  to keep the raw data. Queue size S 
 * is configurable.
 * 
 * When a new 
 * measurement is added to the list of measurements, we check if 
 * configured window size == queue size,
 * If yes then earliest element is kicked out. (An increase
 * in window size will not reclaim the element.) At the same time
 * a lazy-initialized Statstics object is created and used to update 
 * a global/singleton variable known as the ticker.
 *  
 * Once the ticker is updated, the producer submits tasks to 
 * thread pool. If 5 subscribers, then 5 tasks. Each task would send the 
 * content of the global ticker to one subscriber. 
 * 
 * -- Subscriber For Filtered Events - design notes --
 * If a subscriber has a predicate, then this is checked at task creation time.
 * 
 * -- mean calculation --
 * If the moving window size is unchanged, then in each add(), we could 
 * quickly update the sample mean like 
 * 
 *     (oldMean * windowsize - earliestValue + newValue)/windowSize
 *
 * But this algorithm would be problematic if add() is called on multiple threads.
 * 
 * -- other statistics calculation --
 * For a large sample (like 100 billion), it's important to realize that 
 * pre-sorting is either required or speeds up many common statistics.
 * So before we compute any one statistic, we will lazily sort sample and cache
 * it, as an optimization.
 * 
 * required by : percentil, median, Interquartile mean, 
 * speeds up : mode. Indeed my getMode() takes advantage of the pre-sorting.
 * 
 * -- lazy initialization --
 * Since the pre-sorting can be expensive but may not be used (if getMean() 
 * is the only method actually used by clients), it is done only on demand. 
 * Result is saved in the Statistics object and immutable.
 * 
 * -- subscriber registration --
 * All subscribes are attached to a single message queue. 
 * 
 * -- unit tests --
 * There's a test class for Statistics, esp. the mode and percentile calculations.
 * 
 * There's also a test class for synchronous receiver and asynchronous onMsg.
 * 
 * The asynchronous tests are not industrial-strength tests. There's 
 * no assertEqual() to verify 
 * expected output. I construct test cases and compare the console output
 * against my expectation. There are many ways to test a multi-threaded
 * application like this one.
 */
package com.hsbc.slidingWindow;

