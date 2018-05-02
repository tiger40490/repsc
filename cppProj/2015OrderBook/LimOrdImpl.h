#ifndef LIMORDIMPL_H_
#define LIMORDIMPL_H_

#include "Util.h"

class LimOrdImpl {
public:
	enum BuySellEnum {
		B = 'B', S = 'S', BAD_FORMAT
	};
	static BuySellEnum const lookupBuySell(const char b_or_s) {
		if (b_or_s == 'B')
			return B;
		if (b_or_s == 'S')
			return S;
		return BAD_FORMAT;
	}
	LimOrdImpl(const char * const _id, const char _bs, const char * const _qty,
			const char * const _px) :
		id(atoll(_id)),
		bs(lookupBuySell(_bs)), px(atof(_px)), qty(
				atoi(_qty)) {	}
	~LimOrdImpl() {
		//cout << "~LOImpl() " << id << endl;
	}
	unsigned int const getqty() const{
		return qty;
	}
	friend ostream & operator <<(ostream & os, const LimOrdImpl & p);
	friend class LimitOrder;
	const unsigned long long id;
	const BuySellEnum bs;
	const long px;
private://above are const; below are mutable, needs protection by a mutex
	unsigned int qty;
};
ostream & operator<<(ostream &os, LimOrdImpl::BuySellEnum const& p) {
	if (p == LimOrdImpl::B)
		os << "Buy ";
	if (p == LimOrdImpl::S)
		os << "Sell";
	return os;
}

#endif /* LIMORDIMPL_H_ */
