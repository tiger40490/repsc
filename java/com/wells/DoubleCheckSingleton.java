package com.wells;

public class DoubleCheckSingleton {
	private static DoubleCheckSingleton inst = null;
	private volatile boolean isConstructed = false;
	private DoubleCheckSingleton() {
		/* other construction steps */
		this.isConstructed = true; //last step
	}
	DoubleCheckSingleton getInstance() {
		if (inst != null && inst.isConstructed) return inst;
		synchronized(DoubleCheckSingleton.class) {
			if (inst != null && inst.isConstructed) return inst;
			
			
/**This design makes uses of volatile feature that's reputed to be java5
*
* Without the isConstructed volatile field, an incomplete object's 
* address can be assigned to inst, so another thread entering getInstance()
* will see a non-null inst and use the half-cooked object :(
* 
* The isConstructed check ensures the construction has completed
*/
			return inst = new DoubleCheckSingleton();
		}
	}
}
