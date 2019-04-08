package com.wells;
import java.util.concurrent.locks.*;
/**
 * The underlying queue was designed for single-threaded use. We now provide a thread-safe facade to
 * protect it.
 * My blogpost https://wp.me/p74oew-7mE provides more details.
 */
interface PositiveIntQueueForSingleThread {
	int elementCount();
	void enqueue(int i);
	/** returns 0 to indicate empty queue
	 */
	int dequeue();
}

/**Designed for a single producer thread + a single consumer thread. Not designed for 3 or more threads.
 */
public class UnboundedQFor1Producer1Consumer {
	private PositiveIntQueueForSingleThread q; // to be constructed somehow
	private volatile boolean isUnsafe = true; //the "red alert" flag
	private final Lock lock = new ReentrantLock();

	/**	This method runs on the consumer thread and always 
	 * requires locking, whether isUnsafe or not.
	* 
	* Returns 0 to indicate empty queue. Notification 
	* not needed -- a common design in practice.
    */
	int consume1element() {
		this.lock.lock();
		int ret = this.q.dequeue();
		if (this.isUnsafe == false) {
			// Alert is currently off, so we will check whether to turn it on.
			
			//size() can run concurrently with unsynchronized enqueue() 
			// and will return a snapshot value, but it is still a valid value.
			// In java, 32-bit integer update is atomic
			//
			// this.isUnsafe flag is off, and any concurrent unsynchronized enqueue() 
			// will never turn it ON, regardless of visibility of the write.
			if (q.elementCount() <= 2) this.isUnsafe= true;
		}
		this.lock.unlock();
		return ret;
	}

	/**This method runs on the producer thread. It locks only when needed.
	 * So if producer thread is busy producing but consumer 
	 * thread seldom calls consume(), then this method won't need locking:)
	 */
	void produce1element(int item) {
		if (this.isUnsafe) {
			this.lock.lock();
		}
		
		//Q: We want this unsynchronized update to be visible 
		// to the other (i.e. consumer) thread but is it? 
		// I think so, thanks to the volatile field. 
		//
		// If not visible, 
		// q.size() in the consumer thread will fail to reflect this 
		// increment, but that's Fine. Alert would get turned ON more
		// than necessary but that is leaning to the safer side
		this.q.enqueue(item); 
		
		if (this.isUnsafe) {
			if (q.elementCount() > 2) this.isUnsafe= true;
			this.lock.unlock();
		}
	}
}
