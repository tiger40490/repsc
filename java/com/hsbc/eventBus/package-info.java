/** Major java6 features
 * 1) generic wildcard
 * 2) thread wait/notify
 * 3) concurrent producer/consumer using a thread-safe queue
 * *) thread pool executor
 * 
 * There could be a backlog of messages in the message queue, so the 
 * publisher thread should not bypass the backlog and use the new
 * message to trigger the callbacks. Instead, it's 
 * more scalable to have a dispatcher thread watching the queue and
 * sending Runnable/Callable tasks to a thread pool. Each task would 
 * run a 
 * single callback. Each task has a single subscriber and a single 
 * message. The task basically 
 * encapsulates theSubscriber.onMsg(theMessage). If there are 5 
 * subscribers for a message, then 5 tasks.
 * 
 * -- subscriber registration --
 * Each message type (such as PriceMessage or TradeMessage) will 
 * maintain a collection of subscribers. The collection will be a
 * thread-safe collection, so multiple threads can add to it.
 * 
 * Deregistration is a feature not requested.
 * 
 * Dispatcher will be the only (?) thread reading this collection. 
 * The method is sweepAllKnownQueuesOnce().
 * 
 * -- How the dispather is notified --
 * Dispatcher thread runs a sweepAllKnownQueuesOnce() method. This 
 * method should not but could run for a long time. This method removes
 * each message from the message queues. Then it creates Runnable 
 * tasks based
 * on it and adds these tasks to the thread pool. Once it removes all 
 * items from a message queue it would go into wait() on a monitor 
 * object. It will be awaken when any publisher thread calls notify() 
 * on the same monitor.
 * 
 * -- Subscriber For Filtered Events - design notes --
 * Before dispatcher creates a Runnable task, it will check the 
 * subscribes's predicate against the incoming message. 
 * If false, then don't dispatch the task.
 * 
 * Performance requirement and assumption: Predicates run on the 
 * dispatcher thread, so must be quick and cheap, and won't overload  
 * dispatcher thread.
 * 
 * -- Conflation design notes --
 * 
 * Suppose a conflation-mode IBM price message comes in. Then all previous 
 * IBM prices messages should be removed.
 * 
 * Policy -- any Runnable task already created will not be cancelled,
 * though ThreadPoolExecutor.getQueue.remove(Runnable) is available,
 * if needed. Any outdated IBM price message in message queue 
 * (queuing to enter 
 * thread pool) will be removed. If we use ConcurrentLinkedQueue as 
 * message queue
 * then we can remove() on it repeatedly to remove all outdated 
 * IBM prices. I feel this should happen on the publisher thread not 
 * the dispatcher thread. ConcurrentLinkedQueue can cope with concurrent 
 * write by dispatcher and publisher threads.
 * 
 * -- unit tests --
 * These are not industrial-strength tests. There's no assertEqual() to verify 
 * expected output. I construct test cases and compare the console output
 * against my expectation. There are many ways to test a multi-threaded
 * application like this one.
 */
package com.hsbc.eventBus;

