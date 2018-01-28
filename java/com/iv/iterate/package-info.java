/** 
 * 
 * Please see also javadoc in the source code, esp. in FilterIteratorImplByDecoration.java
 * 
 * -- contract between hasNext() and next() methods --
 * https://docs.oracle.com/javase/7/docs/api/java/util/Iterator.html#hasNext() 
 * gives the general rules that all iterators are expected to follow. 
 * 
 * hasNext() will returns true if next() would return an element 
 * rather than throwing an exception
 * 
 * It is sometimes justifiable to deviate from these rules if the requirement is
 * sufficiently complex, making the rules hard to enforce.
 * 
 * Our FilterIterator is fairly complex in a concurrent modification 
 * context. However, I have stuck to the rules to my best.
 * 
 * -- Concurrent access to the same underlying collection --
 * Concurrent modification to the colleciton would mess up not only 
 * our fitering iterator but also traditional iterators. It's not
 * my job to offer any protection.
 * 
 * Concurrent access to the same filtering iterator object is indeed 
 * supported and protected using a simmple lock.
 * 
 * If 2 unrelated filtering iterator objects are scanning the same 
 * collection,
 * then they don't interfere with each other. There's no shared mutable state
 * between them, assuming the underlying collection is not changing.
 * 
 * -- tests --
 * TestAll.java will run all tests.
 * 
 */
package com.iv.iterate;