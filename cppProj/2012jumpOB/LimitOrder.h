#include "LOImpl.h"

#ifndef MESSAGE_H_
#define MESSAGE_H_
class LimitOrder;
typedef list<LimitOrder*> ListType;
typedef ListType::iterator ListItrType;
//void dump2(ListType * const anchorList, ListItrType const anchorPos);

class LimitOrder {
public:
	enum OrderStateEnum {
		LIVE, BAD_FORMAT, REMOVED
	};
	LimitOrder(char const * const id, char const bs, char const * const qty,
			char const * const px) :
		impl(new LOImpl(id, bs, qty, px)) {
		if (impl->id <= 0 || impl->qty <= 0 || impl->px <= 0 || impl->bs
				== LOImpl::BAD_FORMAT) {
			orderState = BAD_FORMAT;
		} else {
			orderState = LIVE;
		}
	}
	const unsigned int id() const {
		return impl->id;
	}
	const LOImpl::BuySellEnum buySell() const {
		return impl->bs;
	}
	const double px() const {
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
		orderState = REMOVED;
		homeList->erase(homePosition);
	}
	void pushInto(ListType& tmpList){
		tmpList.push_back(this);
		this->homePosition = --(tmpList.end());
		this->homeList = &tmpList;
	}
private:
	LOImpl * const impl;
	OrderStateEnum orderState;
	//These 2 fields enables efficient removal from linked list
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
//void dump2(ListType * const anchorList, ListItrType const anchorPos) {
//	cout<<(*anchorPos)->id()<<" passed to dump2()\n";
//	for (ListItrType i = anchorList->begin();; ++i) {
//		if (i == anchorList->end())
//			break;
//		cout << &i<<" id-" << (*i)->id() << " ";
//		if (i == anchorPos) {
//			cout << "found anchorPos!!!!\n\n\n";
//			break;
//		}
//	}
//}
#endif /* MESSAGE_H_ */
