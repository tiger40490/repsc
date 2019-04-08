#include "Util.h"
#ifndef ORDLOOKUP_H_
#define ORDLOOKUP_H_
class LimitOrder;

unsigned int const howManyOrders = 99999;//configurable
/* High level assumptions for the entire order book problem.

Assumption: If a new limit or market order triggers an execution,
exchange always, always broadcasts a Trade message.
If we see an incoming "marketable limit order" but don't see
the expected Trade message, that means exchange has,
for any reason, suppressed the execution,
so the orderbook will reflect this incoming order, but not any
predicted/presumed execution.

Assumption: partial fill is possible. A Trade message could have
a small trade quantity, reducing one (or both) of the
orders identified.

Assumption: for a given name, there might be absolutely no
bid or no ask in the order book, but not "nothing at all".

Assumption: in orderId string, the digits after dot are not
important for now.

Assumption: at the same price level, bid orders queue up. Any of
them can be cancelled, including the first, or last. (Fully tested)
*/

/*This class implements fast lookup by orderId, using array of pointers (or vector of shared_ptr)
 Assumption 1 -- Exchanges generates auto-incrementing orderID's. Here's my reasoning. OrderID's are unique, as stated in the question. If orderID generation isn't continuous, then the generator has 2 choices about the inevitable gap between 2 used numbers. It can keep them forever wasted, or somehow "go back" into a gap and pick a number therein as a new orderID. To do the latter it must keep track of what numbers are already used -- time and space inefficient. There are proven in-memory algorithms to generate auto-increment identity numbers. I assume an exchange would use them. Auto-increment numbers make a good candidate as array index, but what about the total number range?

 Assumption 2 -- each day the number range has an upper limit. Exchange must agree with clients on the format of the orderID. It's likely to be 32 bits, 64 bits etc and won't be a million bits.

 Question 1: Can the exchange use OrderID 98761234 on 2 stocks on the same day? I don't know and i feel it doesn't matter. Here's the reason.

 Case 1: suppose exchange uses an *independent* auto-increment generator for each stock. So IBM and MSFT generators can both generate 98761234. My design would use one array for IBM and one for MSFT. For basket orders, other generator instances might be needed.

 Case 2: suppose exchange uses an independent auto-increment generator for each stock, but each stock uses a non-overlap number range. 98761234 will fall into IBM number range. My design would need to know the number range so as to convert orderID to array index and conserve memory.

 Case 3: suppose exchange uses a singleton auto-increment generator across all stocks. This might be a bottleneck inside the exchange. My design would use a large array. Given Assumption 1, the numbers would be quasi-continuous rather than sparse --for eg less than 50% of the numbers in the range are unused. Suppose the range is S+1, S+2 ... S+N, then my array would be allocated N elements. There's a limit on N in reality. Every system is designed for a finite N -- no system can handle 10^9999 (that's one followed by ten thousand zeros) orders in a day. Each array element is a pointer. For a 64-bit machine, N elements take 64N bits or 8N bytes. If I have 640GB memory, N can be 80 billion but not higher. To scale out horizontally, we would hope Case 1 or 2 is the case.

 Therefore the answer to Question 1 shows array of pointer is feasible for the purpose of lookup by orderID. In a real system hash table is likely to be time/space efficient. Tree based map has logN time complexity. 
 */
class OrdLookup {
	unsigned long long const idBase; //configurable
	vector<LimitOrder*> orderLookup;
public:
	OrdLookup() : idBase(1000000000000240),
		orderLookup( howManyOrders, NULL ) {}

	~OrdLookup() {
		//cout << "~OrdLookup() calling dump()...\n";
		//dump();
	}
	void save(LimitOrder * const newOrder) {
		//cout<<orderLookup.size()<<" " <<newOrder->id() - idBase<<endl;
		orderLookup[newOrder->id() - idBase] = newOrder;
	}
	void nullify(unsigned int id) {
		orderLookup[id - idBase] = NULL;
	}
	LimitOrder* operator[](unsigned long long const id) const {
		LimitOrder * ret = orderLookup[id - idBase];
		DC<<"orderLookup[xxx] returning "<<ret<<endl;
		return ret;
	}
	void dump() const {//LimitOrder ** const orderLookup) {
		cout << "---- orderLookupAcrossSymbols ----\n";
		for (unsigned int i = 0; i < howManyOrders; ++i) {
			if (orderLookup[i])
				cout << *orderLookup[i] << endl;
		}
		cout << "--------\n";
	}
};
#endif /* ORDLOOKUP_H_ */
