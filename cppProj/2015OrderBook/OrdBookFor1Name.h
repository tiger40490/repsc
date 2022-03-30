#ifndef ORDERBOOKFORONENAME_H_
#define ORDERBOOKFORONENAME_H_

#include "LimitOrder.h"

typedef map<long, ListType> MapType;

class OrdBookFor1Name {
	MapType bidSide, askSide;
	void print(MapType & bidOrAskBook) const {//descending
		//cout<<" v v  print() v v "<<endl;
		MapType::reverse_iterator ri;
		for (ri = bidOrAskBook.rbegin(); ri != bidOrAskBook.rend(); ++ri) {
			//cout<<ri->first<<endl;
			ListType & li = ri->second;
			if (li.empty()) continue;
			cout << "At $" << ri->first << "(" << li.size() << ")\t";
			for (ListItrType liItr = li.begin(); liItr != li.end(); ++liItr) {
				cout << *liItr << " ";
			}
			cout << endl;
		}
		//cout<<" ^ ^ print() ^ ^ "<<endl;
	}
public:
	void removeEmptyPxLevels() {
		MapType::iterator it =bidSide.begin();
		while (it != bidSide.end()) {
			long px = it->first;
			//cout<<px<<endl;
			ListType & li = it->second;

			if (li.empty()){
			    bidSide.erase(it++);
				DC<<"$"<<px<<" bid px removed"<<endl;
			}else{
		      ++it;
			}
		}
		it = askSide.begin();
		while (it != askSide.end()) {
			long px = it->first;
			//cout<<px<<endl;
			ListType & li = it->second;

			if (li.empty()){
			    askSide.erase(it++);
				DC<<"$"<<px<<" ask px removed"<<endl;
			}else{
		      ++it;
			}
		}
	}
	ListType & get1QueueInOrderBook(LimOrdImpl::BuySellEnum const buySellEnum,
			long const px) {
		if (buySellEnum == LimOrdImpl::B) {
			return bidSide[px];
		}
		if (buySellEnum == LimOrdImpl::S) {
			return askSide[px];
		}
		throw new exception; //validation IS done before calling
	}

	void printOrderBook4col(int const howManyToPrint){//bidSize,bid,ask,askSize,,,
		MapType::reverse_iterator bidItr=bidSide.rbegin();
		MapType::iterator askItr=askSide.begin();
		bool hasBids = true, hasAsks = true;
		const int max2=max(bidSide.size(), askSide.size());
		for (int i=0; i<min(max2,howManyToPrint);++i){
			if (bidItr == bidSide.rend()){
				hasBids = false;
			}
			if (askItr == askSide.end()){
				hasAsks = false;
			}

			int bidQty = 0, askQty=0;
			long bidPx=0, askPx=0;
			if (hasBids){
				bidPx = bidItr->first;
				ListType & li = bidItr->second;
				for (ListItrType liItr = li.begin(); liItr != li.end(); ++liItr) {
					bidQty += (*liItr)->qty();
				}
			}
			if (hasAsks){
				askPx = askItr->first;
				ListType & li = askItr->second;
				for (ListItrType liItr = li.begin(); liItr != li.end(); ++liItr) {
					askQty += (*liItr)->qty();
				}
			}
			if (i) cout<<",";
			cout<<bidQty<<","<<bidPx<<","<<askPx<<","<<askQty;
			if (hasBids) ++bidItr;
			if (hasAsks) ++askItr;
		}
	}
	void printOrderBook2_debug(){//prints the asks and bids separately.
		print(askSide);
		print(bidSide);
	}
};

#endif /* ORDERBOOKFORONENAME_H_ */
