# -- Fundamental assumptions --
#1 Assumption: each packet has a single seq num but can contain 5.5 messages or half a message for example. 

(Incidentally, A "split" message can have two seq numbers 881 and 882, but in my data model a message is not associated with any seq num.)

#2 Assumption: packets must be processed in strict incrementing sequence with no "jump". 

These two assumptions have fundamental implications.

#3 Assumption: Upon a Replace message, we only need to generate a Replace event, which includes the original order ID. Therefore, cancellation of original order is implied and should Not be broadcast as a redundant event adding unnecssary load to network and sender/receivers.

# -- Warehouse container of OOS packet payloads --
I decided to use a std::deque of packet (payloads actually), indexed by their seq nums to hold unprocessed packets, usually received too early i.e. out-of-sequence. 

I use a variable to hold the lowest seq num among the packets in the warehouse. In this warehouse container, all elements before the lowest are subject to deletion from the container, so as to control memory footprint. Without this control, warehouse container would grow forever .. memory leak!

## An alternative to deque is an unordered_map<seqNum, payload>. 
I feel deque offers the potential of superior CPU cache efficiency, even though some tuning and profiling is required to realize this potential.

## Another popular alternative is a ring buffer pre-allocated with sufficient capacity. 
Pre-allocation is the key benefit compared to dynamical containers in STL. What if exchange were to send a "grossly out-of-sequence packet" like sequence number 987,654,321 when we expect #572? The ring buffer would need huge capacity or become sparse to cope with it. In reality, however, exchanges always send packets in-sequence but IP layer routing can deliver them out-of-sequence, so the delay of the expected packet (#572) will never be so severe. 

# -- Split message solution 1 (not tested) --
To deal with a partial message received-but-unprocessed, I copy it to a singleton "stub" buffer (sized rather large, even though each partial message size is below 34 bytes). Normally this stub buffer is empty. When not empty, it would contain a single received-but-unprocessed partial message of size 33 or shorter. In such a situation, we would wait for the "second half" contained in the next expected packet, either in the warehouse or the next onUDP(). Meanwhile, any unexpected i.e. out-of-sequence packets must be warehoused i.e. copied to a vector and saved in the warehouse container.

Merging the stub buffer with the next packet is a design challenge. My Goal is to minimize memory allocation. Therefore, my stub buffer is rather large, so that without further allocation I can append the "second-half" and all subsequent bytes of an entire packet.

Such a stub buffer needs at least 66KB capacity if we ever "append" a big UDP packet from the incoming buffer. (For TCP, the incoming buffer can be much larger.) Therefore, I want this stub buffer to be a persistent singleton, not created repeatedly. One implementation is a static local variable, encapsulated in onUDP() function.

# -- Split message solution 2 (not implemented) --
In the onUDP() function, I would modify the parameter 'len' to be a reference param. When a partial message is detected, I will set 'len' to the length of that partial message. Thereafter, the caller of onUDP will notice len is not zero. Suppose len = 11, the caller will save the remaining 11 bytes of the old buffer and prepend it to the next buffer. However, the prepend has to be precise:
* the next packet's size information should increase by 11.
* the 11 bytes should come right after the next packet header, right before the 2nd half of the message.

# -- Efficient payload cloning --
Cloning the buffer is relatively expensive in terms of heap allocation. I try to minimize it.

Cloning is probably required when we warehouse a packet, when it is received out-of-sequence for example. Without cloning, the buffer could be overwritten by the next packet coming down the wire.

When warehousing is not required, I make do without cloning, to gain efficiency. I use reinterpret_cast to pick apart the data fields, with zero copy. The endianness conversion, however, is now in-place. During the conversion, the original buffer content is modified. Buffer is not treated as immutable! In other words, the physical bytes of the packet is modified during the endianness conversion. Some programmers may find it unexpected.

I classify my design trade-off as quick-n-dirty. Quick as in simple and fast. Dirty as in unconventional. May give subtle surprises in the future.

One of those subtle thing to remember is -- when an out-of-sequence packet is warehoused, it can't (easily) be saved in the original format -- Its packet header has already been converted so as to read its sequence number. By luck (actually by design), this very sequence number is the index used to locate the packet within the warehouse, so we have it already. Therefore, only the original payload is warehoused.

# -- Efficient broadcast --
I think output socket is one of the simplest and fastest interfaces for broadcast of events to multiple subscribers. Another possible output interface is a messaging bus.

In this toy program, I am required to save the output to a file. Therefore, I have decided to forgo efficiency and simply dump each event message to the same file.

# -- dev-only, non-production files --
Source code in a few files are quick-n-dirty because these are strictly for dev-testing only, not production:
* PacketBuilder.h
* main.cc
* ser4test() in messages.h
* actionRecorder in Parser.*
* dumpBuffer() in utils.cc

# -- Coding convention notes --
Due to lack of time, many rough edes and loose ends..

* char return type -- is used in many functions as status code. Status can be checked in the future.

* templates -- A few simple template function/classes were thrown together in my solution, but not fully justified. In a bigger project templates would be evaluated against many design tradeoffs.

* Capitalized filenames -- Only Capitalized filenames define classes, where the class name is the file name. In messages.h, there are many small and similar classes .. better maintained as a unit, based on my experience.

* "global" functions and variables -- many are implemented as static members. They can become non-static members or stand-alone classes.

* Many member functions are implemented in headers. They should probably go into implementation files. However, template functions must remain in headers.

* reinterpret_cast -- controversial and non-portable, but I have seen it used in high-performance production codebase on linux.

* virtual functions -- I used very few of them. Instead, I prefer templates.

* raw array vs dynamic containers -- in general, I prefer fixed arrays instead of dynamic containers because on-demand heap allocation is expensive at run-time when the container needs reallocation. 
  * the 'actionRecorder' container is not used in production.. no efficiency consideration.
  * the 'workers' lookup table is static and never grows after initilization. In produciton codebase, raw array is preferrable, otherwise perfect-hash.
  * the 'warehouse' data structure is discussed in a dedicated section