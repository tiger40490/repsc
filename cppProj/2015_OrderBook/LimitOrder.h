#ifndef LIMITORDER_h_
#define LIMITORDER_h_

#include "LimOrdImpl.h"

class LimitOrder; // fwd declare to help the typedef
typedef list<LimitOrder*> ListType;
typedef ListType::iterator ListItrType;

class LimitOrder {
public:
	enum OrderStateEnum {
		LIVE, BAD_FORMAT, REMOVED
	};
	LimitOrder(char const * const id, char const bs, char const * const qty,
			char const * const px) :
		impl(new LimOrdImpl(id, bs, qty, px)) {
		if (impl->id <= 0 || impl->qty <= 0 || impl->px <= 0 || impl->bs
				== LimOrdImpl::BAD_FORMAT) {
			orderState = BAD_FORMAT;
		} else {
			orderState = LIVE;
		}
	}
	const unsigned long long id() const {
		return impl->id;
	}
	const LimOrdImpl::BuySellEnum buySell() const {
		return impl->bs;
	}
	const long px() const {
		return impl->px;
	}
	const unsigned int qty() const {
		return impl->getqty();
	}
	void qty(unsigned int const qty) {
		impl->qty = qty;
	}
	const OrderStateEnum status() const {
		return orderState;
	}
	bool isLive() const {
		return orderState == LIVE;
	}
	bool isDead() const {
		return orderState != LIVE;
	}
	void remove() {
		delete this->impl;
		this->orderState = REMOVED;
		this->homeList->erase(homePosition);
	}
	void pushInto(ListType& tmpList){
		tmpList.push_back(this);
		this->homePosition = --(tmpList.end());
		this->homeList = &tmpList;
	}
private:
	LimOrdImpl * const impl;
	OrderStateEnum orderState;

	//The 2 fields below enable efficient removal from linked list
	ListType * homeList;
	ListItrType homePosition;
};
ostream & operator<<(ostream &os, LimitOrder const& p) {
	if (p.isLive()) {
		os << "(Ord-" << p.id() << " " << p.buySell() << " " << p.qty()
				<< " @ $" << p.px() << ")";
	} else if (p.status() == LimitOrder::REMOVED) {
		os << "(Removed)";
	}
	return os;
}
ostream & operator<<(ostream &os, LimitOrder const * const p) {
	if (p != NULL) {
		os << *p;
	}
	return os;
}
struct OrdLocator{
	const char * str;
	unsigned long long id;
	LimitOrder * ord;
public:
	OrdLocator():str(NULL),id(0), ord(NULL){}
};
#endif /* LIMITORDER_h_ */
