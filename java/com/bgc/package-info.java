/** A 2017 March coding challenge. Requirement document is saved in the same 
 * directory as this java package. 
 * 
 * Feature: read-write lock
 * Feature: concurrent read/write operation 
 * Feature: builder design pattern
 * 
 * Assumption: cityNames can have whitespace in the input file, but they would be 
 * removed automatically. No whitespace is supported on the command line.
 * 
 * Assumption: the input data could someday be processed on multiple threads.
 * 
 * Assumption: Once the input data is digested, we will receive a sequence of 
 * queries, perhaps on multiple threads. Basically a network server.
 * 
 * Assumption: As we answer queries, concurrently new input data can come in.
 * 
 * Design Priority: increase parallelism; minimize locking. (For an example, see 
 * the note on lookup table update.) In general the simplest concurrency design 
 * uses a single global lock whenever we need to read or write on a
 * shared collection. In the degenerate case, just about every important operation
 * would acquire the global lock. We end up with an effectively single-threaded 
 * system. 
 * 
 * -- Design -- 
 * Any pair in the input data represents an edge connecting 2 cities.  At any time 
 * there are a number of disconnected "islands". The next pair could 
 * 1) merge 2 islands or 
 * 2) add a city to an existing island or 
 * 3) create a new island consisting of 2 new cities or 
 * 4) do nothing, if the 2 cities are already on the same island
 * 
 * Any city appears exactly once in the graph, in exactly one of the islands.
 * 
 * All cities are registered in a global lookup table {city -> island}. At a 
 * given time, if 2 given cities are in the same island they are considered 
 * connected.
 * 
 * -- lookup table update during merge --
 * When we move the cities from one "island" to another "island", it's simple to 
 * update the global lookup table (while locking it). Basically, mark each moved 
 * city as belonging to the new island. 
 * 
 * However, simplicity is costly in this case. Simplicity requires holding a 
 * global lock while we iterate each merged city.
 * 
 * The chosen design avoids updating the global lookup table during the merge. 
 * Instead, at end of merge, the "acquired" island is modified to "point to" the 
 * merged island. Therefore, if the lookup table says Boston is in Island_55, we 
 * could find Island_55 now points to (was absorbed into) Island_33, which points 
 * to Island_11.
 * 
 * This design avoids global locking at the expense of query time. 
 * - if merge is infrequent then favor the simple design. 
 * - if merge is frequent, then under the assumptions 
 * above, merge can happen concurrently as queries. So 
 * this design could perform better.
 * 
 * --While merging island11 into Island22, Thread 2 adds city AA into Island11?--
 * 
 * AA will register as part of Island11, just like all previous cities in Island11. 
 * 
 * -- While creating island with 2 new cities A/C, Thread2 receives A/W? --
 * By right, Thread 2 should perform 
 * Scenario 1 - merge, or 
 * Scenario 2 - add W to the A/C island, if W is also new.
 *  
 * Without synchronization, it could make wrong decisions such as 
 * Scenario 3 - create new island with A/W, or 
 * Scenario 2 - add A to W's island
 * 
 * Therefore as a precaution, I grab the global write lock if either city (in a 
 * incoming pair) is newcomer (i.e. Scenarios 2 or 3.) 
 * 
 * All readers would require the reader lock unconditionally, 
 * and would be blocked until the global lookup table update is done. If no 
 * write lock is in use, then read lock would not block.
 * 
 * The read/write lock protects the global lookup table. Any method reading
 * the lookup table would need read lock; any method updating the lookup table
 * would need the write lock.
 */
package com.bgc;