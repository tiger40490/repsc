#include "LimitOrder.h"

#ifndef ORDERBOOKFORONENAME_H_
#define ORDERBOOKFORONENAME_H_
typedef map<double, ListType> MapType;

class OrdBookForOneSymbol {
	MapType bidBook, askBook;
	double highestBid, lowestAsk, lastTradePx;
	unsigned int cummulativeQty;
	void print(MapType & book) const {
		MapType::reverse_iterator ri;
		for (ri = book.rbegin(); ri != book.rend(); ++ri) {
			ListType & li = ri->second;
			//li.remove_if(mem_fun(&LimitOrder::isDead));//perhaps not needed
			if (li.empty()) {
				//cout<<"empty list found. Unexpected\n";
				continue;
			}

			cout << "At $" << ri->first << "(" << li.size() << ")\t";
			for (ListItrType liItr = li.begin(); liItr != li.end(); ++liItr) {
				cout << *liItr << " ";
			}
			cout << endl;
		}
	}
	static void printPriceLevels(MapType & book) {
		return; // disabled
		MapType::iterator fi;
		cout << "root";
		for (fi = book.begin(); fi != book.end(); ++fi) {
			cout << "->" << fi->first;
		}
		cout << endl;
	}
	void scanBestBid() {//erase any empty std::list on the map
		MapType::reverse_iterator ri;
		for (ri = bidBook.rbegin(); ri != bidBook.rend();) {
			ListType & li = ri->second;
			if (li.empty()) {
				printPriceLevels(bidBook);
				bidBook.erase((++ri).base());
				printPriceLevels(bidBook);
				//cout << "now itr -> " << itr->first << endl;
				continue;
			} else {
				cout << highestBid << " (highestBid) dropping to " << ri->first
						<< endl;
				highestBid = ri->first;
				return;
			}
			++ri;
		}
	}
	void scanBestAsk() {
		MapType::iterator i;
		for (i = askBook.begin(); i != askBook.end();) {
			ListType & li = i->second;
			if (li.empty()) {
				printPriceLevels(askBook);
				askBook.erase(i);
				printPriceLevels(askBook);
				//cout << "now itr -> " << i->first << endl;
				++i;
				continue;
			} else {
				cout << lowestAsk << " (lowestAsk) bumping to " << i->first
						<< endl;
				lowestAsk = i->first;
				return;
			}
		}
	}
public:
	void printCummulative(vector<char const*> const & dto) {
		double qty = atof(dto[1]);
		double px = atof(dto[2]);
		if (px <= 0 || qty <= 0) {
			return;
		}
		if (px == lastTradePx) {
			cummulativeQty += qty;
		} else {
			lastTradePx = px;
			cummulativeQty = qty;
		}
		cout << cummulativeQty << " @ " << lastTradePx << endl;
	}
	OrdBookForOneSymbol() :
		highestBid(0), lowestAsk(999999999), lastTradePx(0), cummulativeQty(0) {
	}
	void updateBestAfterRemove(LOImpl::BuySellEnum const bs, double const px) {
		if (bs == LOImpl::B && px == highestBid) {
			ListType & li = bidBook[highestBid];
			// not needed li.remove_if(mem_fun(&LimitOrder::isDead));

			// if any valid bid remains at this level, then no update needed
			if (li.empty())
				scanBestBid();
		} else if (bs == LOImpl::S && px == lowestAsk) {
			ListType & li = askBook[lowestAsk];
			//not needed li.remove_if(mem_fun(&LimitOrder::isDead));

			// if any valid ask remains at this level, then no update needed
			if (li.empty())
				scanBestAsk();
			else {
				cout << "lowestAsk remains\n";
			}
		}
	}
	void updateBestAfterAdd(LimitOrder const * const newOrder) {
		if (newOrder->isDead())
			return;
		if (newOrder->buySell() == LOImpl::B) {
			if (newOrder->px() > highestBid) {
				highestBid = newOrder->px();
			}
		} else if (newOrder->buySell() == LOImpl::S) {
			if (newOrder->px() < lowestAsk) {
				lowestAsk = newOrder->px();
			}
		}
	}

	ListType & get1QueueInOrderBook(LOImpl::BuySellEnum const buySellEnum,
			double const px) {
		if (buySellEnum == LOImpl::B) {
			return bidBook[px];
		}
		if (buySellEnum == LOImpl::S) {
			return askBook[px];
		}
		throw new exception; //validation IS done before calling
	}
	void printMidQuote() const {
		cout << "mid = $";
		if (highestBid <= 0 || lowestAsk >= 99999) {
			cout << "NAN";
		} else {
			cout << (lowestAsk + highestBid) / 2.0;
		}
		cout << "  <-- $" << highestBid << " // $" << lowestAsk << endl;
		if (highestBid >= lowestAsk) {
			cout << "    ...bid/ask inverted. Executing..\n";
		}
	}
	void printCurrentOrderBook() {
		print(askBook);
		print(bidBook);
	}
};

#endif /* ORDERBOOKFORONENAME_H_ */
